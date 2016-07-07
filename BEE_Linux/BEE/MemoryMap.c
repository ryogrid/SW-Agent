#include "inc.h"

static MemMapInfo memmapHead;
static MemMapInfo *lpMemMapInfoHead = NULL;

int SysCallMemoryUnmap(void *_start, unsigned long _length);

void InitBeeMemory()
{
    memset(&memmapHead, 0, sizeof(MemMapInfo));
    lpMemMapInfoHead = &memmapHead;
}

int FinalizeBeeMemory()
{
    MemMapInfo *cur, *next;

    cur = lpMemMapInfoHead->next;
    while(cur != NULL){
        next = cur->next;
        SysCallMemoryUnmap((void*)cur->start, cur->end-cur->start);
    }
    return 1;
}

void PrintMemMapInfo()
{
    MemMapInfo *mi;
    mi = lpMemMapInfoHead;
    printf("%p [%08lx-%08lx] %p\n",mi,  mi->start, mi->end, mi->next);
    mi = lpMemMapInfoHead->next;
    while(mi != NULL){
        printf("%p [%08lx-%08lx]\n", mi, mi->start, mi->end);
        mi = mi->next;
    }
}

static void AddMemMapInfo(int fd, unsigned long _start, unsigned long _length, unsigned long _prot)
{
    MemMapInfo *mi;
    
    mi = (MemMapInfo*)mAlloc(sizeof(MemMapInfo));
    mi->start = PAGE_START(_start);
    mi->end = PAGE_ALIGN(_start+_length);
    mi->flags = _prot;
    mi->next = NULL;
/*    
    mi->pathname = NULL;
    if(beefd >= 0){
        beeio = GetBeeIOHandle(beefd);
        mi->pathname = strdup(PathFindFileNameA(beeio->filepath));
    }
*/  
    {
        MemMapInfo *cur, *prev;
        cur = lpMemMapInfoHead->next;
        prev = lpMemMapInfoHead;
        while(cur != NULL){
            if(cur->start >= mi->end){
                prev->next = mi;
                mi->next = cur;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        prev->next = mi;
    }
    return;
}

static void RemoveMemMapInfo(unsigned long _start, unsigned long _length)
{
    //TODO
    MemMapInfo *cur, *prev;
    
    if(lpMemMapInfoHead == NULL){
        return;
    }

    cur = lpMemMapInfoHead->next;
    prev = lpMemMapInfoHead;
    while(cur != NULL){
        if( cur->start == _start && 
            cur->end == _start+_length){
            prev->next = cur->next;
            free(cur->pathname);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

/*************************************************************************************
 * for parent process
 *************************************************************************************/
int ReadProcessMemory(pid_t pid, void *addr, void *buf, int bufsize)
{
    int i;
    unsigned long tmp;
    int origsize;
    char *tmpbuf;
    void *p;

    origsize = bufsize;
    if(bufsize % sizeof(int) != 0){
    	bufsize = (bufsize/sizeof(int)) * sizeof(int);
    }
    tmpbuf = (char*)malloc(sizeof(char)*bufsize);
    p = (void*)tmpbuf;
    
    errno = 0;
    for(i=0; i<bufsize; i+=sizeof(int)){
        tmp = ptrace(PTRACE_PEEKDATA, pid, addr, NULL);
        if(tmp == 0xFFFFFFFF){
            if(errno != 0){
                perror("ptrace");
                return -1;
            }
        }
        *((unsigned long*)p) = tmp;
        p += 4;
        addr+= 4;
    }
    memcpy(buf, tmpbuf, origsize);
    free(tmpbuf);
    return 1;
}

int WriteProcessMemory(pid_t pid, void *addr, void *buf, int bufsize)
{
    int i;
    unsigned long tmp;

    errno = 0;
    for(i=0; i<bufsize; i+=sizeof(int)){
        tmp = ptrace(PTRACE_POKEDATA, pid, addr, buf);
        if(tmp == 0xFFFFFFFF){
            if(errno != 0){
                perror("ptrace");
                return -1;
            }
        }
        buf += 4;
        addr+= 4;
    }
    return 1;
}

int ReadProcessInfoMemory(pid_t pid, ProcessInfo *dst)
{
    if(ReadProcessMemory(pid, (void*)GetProcessInfo(), (void*)dst, sizeof(ProcessInfo)) < 0){
        return -1;
    }
    return 1;
}

static void DeleteCodeAreaMemMapInfo(LinkedList *list)
{
    int i;
    for(i=0; i<GetLinkedListSize(list); i++){
        MemMapInfo *mi;
        mi = (MemMapInfo*)GetLinkedListItem(list, i);
        if(mi->flags & PROT_EXEC){
            RemoveLinkedListItem(list, i);
            free(mi);
        }
    }
}

LinkedList *GetChildMemMapInfoList(pid_t pid, ProcessInfo *pi)
{
    LinkedList *list;
    MemMapInfo tmp;
    unsigned long addr;

    if(ReadProcessMemory(pid, (void*)&memmapHead, (void*)&tmp, sizeof(MemMapInfo)) < 0){
        printf("ReadProcessMemory\n");
        return NULL;
    }
    if(tmp.next == NULL){
        return NULL;
    }
    
    addr = (unsigned long)tmp.next;
    list = NewLinkedList();
    while(1){
        MemMapInfo *mi;
        if(ReadProcessMemory(pid, (void*)addr, (void*)&tmp, sizeof(MemMapInfo)) < 0){
            printf("ReadProcessMemory\n");
            return NULL;
        }
        mi = (MemMapInfo*)malloc(sizeof(MemMapInfo));
        memcpy(mi, &tmp, sizeof(MemMapInfo));
        AddLinkedListItem(list, (void*)mi);
        if(mi->next == NULL){
            break;
        }
        addr = (unsigned long)mi->next;
    }
    DeleteCodeAreaMemMapInfo(list);
    return list;
}

int DeleteMemMapInfoList(LinkedList *list)
{
    int i;
    MemMapInfo *item;
    for(i=0; i<GetLinkedListSize(list); i++){
        item = (MemMapInfo*)GetLinkedListItem(list, i);
        if(item != NULL){
            free(item);
        }
    }
    DeleteLinkedList(list);
    return 1;
}

/*************************************************************************************
 * brk
 *************************************************************************************/
int SysCallBrk(unsigned int brk)
{
    void* newBreak;
    unsigned long prot = PROT_READ | PROT_WRITE;
    unsigned long flags = MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS;
    ProcessInfo *pi;
    
    pi = GetProcessInfo();
    if(brk <= pi->brk ){ //end == 0
        return (int)pi->brk;
    }
    else{
        newBreak = (void*)MemoryMap(-1, pi->brk, PAGE_ALIGN(brk)-pi->brk, prot, flags, 0);
        if(newBreak == MAP_FAILED){
            return pi->brk;
        }
        pi->brk = PAGE_ALIGN(brk);
    }
    return (int)brk;
}

/*************************************************************************************
 * mmap
 *************************************************************************************/
#define MEM_START_ADDR (0x01000000)

struct mmapArgs
{
    unsigned long addr;
    unsigned long len;
    unsigned long prot;
    unsigned long flags;
    unsigned long fd;
    unsigned long offset;
};

int MemoryMap(int fd, unsigned long start, unsigned long length, unsigned long _prot, unsigned long flags, unsigned long offset)
{
    unsigned long addr;
    length = PAGE_ALIGN(length);
    
    if((flags & MAP_SHARED)){
        return (int)MAP_FAILED;
    }
    if(_prot&MAP_ANONYMOUS){
        MemMapInfo *mi;
        _prot |= MAP_FIXED;
        start = MEM_START_ADDR;
        mi = lpMemMapInfoHead->next;
        
        while(mi != NULL){
            if( (start >= mi->start && start < mi->end) || (start+length > mi->start && start+length < mi->end) ){
                mi = mi->next;
                start = mi->end;
            }
            else if(start+length < mi->start){
            	break;
            }
        }
        printf("start:%08lx\n", start);
    }
    addr = (unsigned long)mmap((void*)start, length, _prot, flags, fd, offset);
    if(addr == (unsigned long)MAP_FAILED){
        return addr;
    }
    AddMemMapInfo(fd, addr, length, _prot);
    return addr;
}

int SysCallMemoryMap(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int ret;
    struct mmapArgs *a;

    a = (struct mmapArgs*)arg1;
    ret = MemoryMap(a->fd, a->addr, a->len, a->prot, a->flags, a->offset);
    return ret;
}

int SysCallMemoryMap2(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int ret;
    ret = MemoryMap(arg5,
		    (unsigned long)arg1, (unsigned long)arg2,
		    (unsigned long)arg3, (unsigned long)arg4,
		    (unsigned long)arg6);
    return ret;
}

/*************************************************************************************
 * munmap
 *************************************************************************************/
int SysCallMemoryUnmap(void *_start, unsigned long _length)
{
    int ret;
    ret = munmap(_start, _length);
    RemoveMemMapInfo((unsigned long)_start, _length);
    return ret;
}


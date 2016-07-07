#define _GNU_SOURCE
#include "inc.h"

typedef struct _dumpinfo
{
    ProcessInfo *processInfo;
    LinkedList *list;
#ifdef __NR_set_thread_area
    struct user_desc *tlsInfo;
#endif
} dargs;

static int WriteElfHeader(int fd, LinkedList *list);
static int WriteElfProgramHeader(int fd, LinkedList *list);
static int WriteNoteSegment(const int fd, pid_t pid, dargs *d);
static int WriteMemorySegments(int fd, pid_t pid, LinkedList *list);


int DumpElfCoreFile(pid_t pid, const char *filename)
{
    int fd;
    LinkedList *list;

    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR|S_IWUSR | S_IRGRP | S_IROTH);
    if(fd < 0){
        perror("open");
        return -1;
    }
    
    {
        dargs args;
        ProcessInfo processInfo;

#ifdef __NR_set_thread_area
        /*get tls segment*/
        struct user_desc tlsInfo;
        if(ReadTLSInfoMemory(pid, &tlsInfo) < 0){
            printf("ReadTLSInfoMemory\n");
            goto err1;
        }
        args.tlsInfo = &tlsInfo;
#endif

        /*get processinfo*/
        if( ReadProcessInfoMemory(pid, &processInfo) < 0){
            printf("ReadProcessInfoMemory\n");
            goto err1;
        }
        args.processInfo = &processInfo;
        
        /*get memory map*/
        if( (list = GetChildMemMapInfoList(pid, &processInfo)) == NULL){
            printf("GetMemMapInfoList\n");
            goto err1;
        }
        args.list = list;

        /* write headers for elf core file */
        if(WriteElfHeader(fd, list) < 0){
            printf("WriteElfHeader\n");
            goto err2;
        }
        if(WriteElfProgramHeader(fd, list) < 0){
            printf("WriteElfProgramHeader\n");
            goto err2;
        }
        /* write memory segments */
        if(WriteNoteSegment(fd, pid, &args) < 0){
            printf("WriteNoteSegments\n");
            goto err2;
        }
        if(WriteMemorySegments(fd, pid, list) < 0){
            printf("WriteMemorySegments\n");
            goto err2;
        }
    }
    /* finalize */
    close(fd); 
    DeleteMemMapInfoList(list);
    return 1;

err2:
    DeleteLinkedList(list);
err1:
    close(fd);
    return -1;
}

static int WriteElfHeader(int fd, LinkedList *list)
{
    Ehdr header;

    memset(&header, 0, sizeof(Ehdr));
    header.e_ident[0] = ELFMAG0;
    header.e_ident[1] = ELFMAG1;
    header.e_ident[2] = ELFMAG2;
    header.e_ident[3] = ELFMAG3;
    header.e_ident[4] = ELFCLASS32;     /*32 bit*/
    header.e_ident[5] = 1; /*little-endian*/
    header.e_ident[6] = 1;
    
    header.e_type       = ET_CORE;
    header.e_machine    = EM_386;//ELF_ARCH;
    header.e_version    = EV_CURRENT;
    header.e_phoff      = sizeof(Ehdr);
    header.e_ehsize     = sizeof(Ehdr);
    header.e_phentsize  = sizeof(Phdr);
    header.e_phnum      = (unsigned short)(GetLinkedListSize(list) + 1);
    header.e_shentsize  = sizeof(Shdr); 
    
    if(write(fd, &header, sizeof(Ehdr)) != sizeof(Ehdr)){
        perror("write");
        return -1;
    }
    return 1;
}

static int WriteElfProgramHeader(int fd, LinkedList *list)
{
    Phdr pheader;
    unsigned long offset, filesize;
    int i;
    
    // write the PT_NOTE entry
    offset = sizeof(Ehdr) + sizeof(Phdr)*(GetLinkedListSize(list) + 1);
    
    // +4 = strlen("CORE")
    filesize =  sizeof(Nhdr) + 4 + sizeof(struct user) +
#ifdef __NR_set_thread_area
                sizeof(Nhdr) + 4 + sizeof(struct user_desc) +
#endif
                sizeof(Nhdr) + 4 + sizeof(ProcessInfo);

/*
                threadNum*(
                + sizeof(Nhdr) + 4 + sizeof(elf_prstatus)
                + sizeof(Nhdr) + 4 + sizeof(user_fpregs));
*/    
    memset(&pheader, 0, sizeof(Phdr));
    pheader.p_type = PT_NOTE;
    pheader.p_offset = offset;
    pheader.p_filesz = filesize;
    
    if(write(fd, &pheader, sizeof(Phdr)) != sizeof(Phdr)){
        return -1;
    }
    
    /*
     * pheader entry
     */    
    pheader.p_type = PT_LOAD;
    pheader.p_align = PAGE_SIZE;
    pheader.p_paddr = 0;

    offset += PAGE_SIZE - ((offset+filesize) & (PAGE_SIZE-1));

    for(i=0; i<GetLinkedListSize(list); i++){
    	unsigned long flag;
    	MemMapInfo *memInfo;
    	memInfo = (MemMapInfo*)GetLinkedListItem(list, i);
        offset += filesize;
        filesize = memInfo->end - memInfo->start;
        pheader.p_offset = offset;
        pheader.p_vaddr = memInfo->start;
        pheader.p_memsz = filesize;
        pheader.p_filesz = filesize;
        
        flag = 0;
        if(memInfo->flags & PROT_READ) { flag |= PF_R; }
        if(memInfo->flags & PROT_WRITE){ flag |= PF_W; }
        if(memInfo->flags & PROT_EXEC) { flag |= PF_X; }
        pheader.p_flags = flag;
        if(write(fd, &pheader, sizeof(Phdr)) != sizeof(Phdr)){
            return -1;
        }
    }
    return 1;
}


static void PrintUserRegs(struct user *u)
{
  struct user_regs_struct *r = &u->regs;

    printf("regs\n");
    printf(" eax: 0x%08lx\n", r->eax);
    printf(" ebx: 0x%08lx\n", r->ebx);
    printf(" ecx: 0x%08lx\n", r->ecx);
    printf(" edx: 0x%08lx\n", r->edx);
    printf(" esi: 0x%08lx\n", r->esi);
    printf(" edi: 0x%08lx\n", r->edi);
    printf(" ebp: 0x%08lx\n", r->ebp);
    printf(" esp: 0x%08lx\n", r->esp);
    printf(" eip: 0x%08lx\n", r->eip);

    printf(" eflags: 0x%08lx\n", r->eflags);
    printf(" orig_eax: 0x%08lx\n", r->orig_eax);
}

/*
static void PrintUserFpuRegs(struct user_fpregs_struct *f)
{
    if(f == NULL){
        printf("NULL po\n");
        return;
    }
    
    printf("FPU regs\n");
    printf(" cwd : 0x%08lx\n", f->cwd);
    printf(" swd : 0x%08lx\n", f->swd);
    printf(" twd : 0x%08lx\n", f->twd);
    printf(" fip : 0x%08lx\n", f->fip);
    printf(" fcs : 0x%08lx\n", f->fcs);
    printf(" foo : 0x%08lx\n", f->foo);
    printf(" fos : 0x%08lx\n", f->fos);
}
*/

static int WriteNote(const int fd, Note *note)
{
    Nhdr nhdr;
    int writesize;
    
    nhdr.n_namesz = strlen(note->name);
    nhdr.n_type = note->type;
    nhdr.n_descsz = note->datasize;

    writesize = 0;
    writesize += write(fd, &nhdr, sizeof(Nhdr));
    writesize += write(fd, note->name, nhdr.n_namesz);
    writesize += write(fd, note->data, note->datasize);
    if(writesize != sizeof(Nhdr) + nhdr.n_namesz + note->datasize){
        return -1;
    }
    return writesize;
}

static int WriteNoteSegment(const int fd, pid_t pid, dargs *d)
{
    Note note;
    char buf[PAGE_SIZE];
    unsigned long offset, filesize, ret, len;
    struct user proc_user;
    struct user_regs_struct *regs;

    LinkedList *list;
    ProcessInfo *processInfo;

    
    filesize = 0;
    memset(&note, 0, sizeof(Note));
    note.name = "CORE";

    list = d->list;
    processInfo = d->processInfo;
    
    //NT_PRXREG
    {
    	int i;
        memset(&proc_user, 0, sizeof(struct user));
        for(i=0; i<sizeof(struct user); i+=sizeof(int)){
	  ((int *)&proc_user)[i/sizeof(int)] = ptrace(PTRACE_PEEKUSER, pid, (void *)i, NULL);
        }
        regs = &proc_user.regs;
        note.type = NT_PRXREG;
        note.data = (void*)&proc_user;
        note.datasize = sizeof(struct user);
        if( (ret = WriteNote(fd, &note)) < 0){
            return -1;
        }
        filesize += ret;
    }
    PrintUserRegs(&proc_user); 

    //prosessinfo
    {
        note.type = NT_PROCESSINFO;
        note.data = (void*)processInfo;
        note.datasize = sizeof(ProcessInfo);
        if( (ret = WriteNote(fd, &note)) < 0){
            return -1;
        }
        filesize += ret;
    }

#ifdef __NR_set_thread_area
    //tlsinfo
    {
    	struct user_desc *tlsInfo;
    	tlsInfo = d->tlsInfo;
    	note.type = NT_TLSINFO;
    	note.data = (void*)tlsInfo;
    	note.datasize = sizeof(struct user_desc);
    	if( (ret = WriteNote(fd, &note)) < 0){
            return -1;
    	}
        filesize += ret;
    }
#endif   
    //padding
    offset = sizeof(Ehdr) + sizeof(Phdr)*(GetLinkedListSize(list)+1);    
    len = PAGE_SIZE - ((offset+filesize) & (PAGE_SIZE-1));
    memset(buf, 0, sizeof(buf));
    if(write(fd, buf, len) != len){
        printf("WriteNoteSegment : write error\n");
        return -1;
    }
    return 1;
}

static int WriteMemorySegments(int fd, pid_t pid, LinkedList *list)
{
    int i, j;
    char data[PAGE_SIZE];

    for(i=0; i<GetLinkedListSize(list); i++){
        MemMapInfo *mi;
        mi = (MemMapInfo*)GetLinkedListItem(list, i);
        for(j=0; j<(mi->end-mi->start); j+=sizeof(data)){           
            if(ReadProcessMemory(pid, 
				 (void*)(mi->start+(unsigned long)j),
				 data, sizeof(data))<0){
                printf("ReadProcessmemory\n");
                return -1;
            }
            if(write(fd, data, sizeof(data)) != sizeof(data)){
                perror("write");
                return -1;
            }
        }
    }
    return 1;
}

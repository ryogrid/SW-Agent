#define _GNU_SOURCE
#include "inc.h"

#define INTERPRETER_NONE 0
#define INTERPRETER_AOUT 1
#define INTERPRETER_ELF	 2

#define LOADER_TYPE_EXEC (1)
#define LOADER_TYPE_CORE (2)

static LoaderFunction lf;
static int loaderType;

static int ReadHeader(int fd, Ehdr *lpEhdr);
static Phdr *ReadElfProgramHeader(int fd, Ehdr *lpEhdr);

#ifdef __DEBUG__
static void PrintElfHeader(Ehdr *header);
static void PrintElfProgramHeader(Phdr *lpPhdr, int hdrNum);
#endif

static int FreeElfProgramHeader(Phdr *lpPhdr);

static int LoadElfExec(int fd, LoaderArg *lpArgs, Ehdr *lpEhdr, Phdr *lpPhdr);
static int LoadElfCore(int fd, LoaderArg *lpArgs, Ehdr *lpEhdr, Phdr *lpPhdr);

/*
static int InitializeElfSymbol(const int fd, Ehdr *header);
static int FinalizeElfSymbol(void);
static int ElfHookFucntion(char *hookfuncname, unsigned long hookfuncaddr);
*/

static int CheckElfBinary(char *buf, unsigned int size)
{
    Ehdr Ehdr;
    
    if(buf == NULL || size < sizeof(Ehdr)){
        return -1;
    }
    memcpy(&Ehdr, (void*)buf, sizeof(Ehdr));
    if(strncmp((char *)Ehdr.e_ident, (char *)ELFMAG, SELFMAG) != 0){
        return -1;
    }
    if(Ehdr.e_ident[EI_CLASS] != ELFCLASS32 || Ehdr.e_machine != EM_386){
        return -1;
    }
    if(Ehdr.e_type == ET_EXEC){
        loaderType = LOADER_TYPE_EXEC;
    }
    else if(Ehdr.e_type == ET_CORE){
        loaderType = LOADER_TYPE_CORE;
    }
    else{
        return -1;
    }
    return 1;
}

static int LoadElfBinary(int fd, LoaderArg *lpArgs)
{
    Ehdr Ehdr;
    Phdr *lpPhdr;
    int ret;

    if(ReadHeader(fd, &Ehdr) < 0){
        return -1;
    }
    lpPhdr = ReadElfProgramHeader(fd, &Ehdr);
    if(lpPhdr == NULL){
        return -1;
    }

#ifdef DEBUG
    PrintHeader(&Ehdr);
    PrintElfProgramHeader(lpPhdr, Ehdr.e_phnum);
#endif
    switch(loaderType){
    case LOADER_TYPE_EXEC:
        ret = LoadElfExec(fd, lpArgs, &Ehdr, lpPhdr);
        break;
    case LOADER_TYPE_CORE:
        ret = LoadElfCore(fd, lpArgs, &Ehdr, lpPhdr);
        break;
    default:
        ret = -1;
        break;
    }
//    FreeElfProgramHeader(lpPhdr);
    return ret;
}

LoaderFunction *GetElfLoaderFunction(void)
{
    lf.load = LoadElfBinary;
    lf.check = CheckElfBinary;
    return &lf;
}

/**********************************************************************************
 *
 * common
 *
 **********************************************************************************/
static int ReadBuf(int fd, int offset, void *lpbuf, int size)
{
    if(lseek(fd, (long)offset, SEEK_SET) != (long)offset){
        perror("lseek");
        return -1;
    }
    if(read(fd, lpbuf, size) < 0){
        perror("read");
        return -1;
    }
    return 1;
}

static int ReadHeader(int fd, Ehdr *lphdr)
{
    return ReadBuf(fd, 0, lphdr, sizeof(Ehdr));
}

static Phdr *ReadElfProgramHeader(int fd, Ehdr *lpEhdr)
{
    int size;
    Phdr *lpPhdr;

    //load program header
     if(lpEhdr->e_phentsize != sizeof(Phdr)){
        return NULL;
    }

    size = lpEhdr->e_phnum * sizeof(Phdr);
    lpPhdr = (Phdr*)mAlloc(size);
    if(ReadBuf(fd, lpEhdr->e_phoff, (void *)lpPhdr, size) == 0){
        free(lpPhdr);
        return NULL;
    }
    return lpPhdr;
}

static int FreeElfProgramHeader(Phdr *lpPhdr)
{
    free(lpPhdr);
    return 1;
}

/**********************************************************************************
 *
 * exec 
 *
 **********************************************************************************/
#ifdef __DEBUG__
static void PrintElfHeader(Ehdr *header)
{
    printf("ELF Header\n");
    printf("type:%d machine:%d version:%d\n",
        header->e_type, header->e_machine, header->e_version);
    printf("entry:%08x phoff:%d, shoff:%d\n",
        header->e_entry, header->e_phoff, header->e_shoff);
    printf("flags:%d ehsize:%d phentsize:%d\n",
        header->e_flags, header->e_ehsize, header->e_phentsize);
    printf("phnum:%d shentsize:%d shnum:%d\n",
        header->e_phnum, header->e_shentsize, header->e_shnum);
    printf("shstr%d\n", header->e_shstrndx);
}

static void PrintElfProgramHeader(Phdr *pheader, int hnum)
{
    int i;
    for(i=0; i<hnum; i++){
        Phdr *ph = &pheader[i];
        printf("program header[%d]: type:%08x offset:%08x vaddr:%08x paddr:%08x\n",
            i, ph->p_type, ph->p_offset, ph->p_vaddr, ph->p_paddr);
        printf("\t filesize:%08x memsize:%08x flags:%08x align:%08x\n",
            ph->p_filesz, ph->p_memsz, ph->p_flags, ph->p_align);
    }
}
#endif

static int MapElfProgram(int fd, Phdr *lpPhdr, int num, ProcessInfo *lpPi)
{
    unsigned long startCodeAddr, endCodeAddr;
    unsigned long startDataAddr, endDataAddr;
    unsigned long bss, brk;
    void *map_addr;
    int i;

    startCodeAddr = ULONG_MAX;
    endCodeAddr = 0L;
    startDataAddr = ULONG_MAX;
    endDataAddr = 0L;
    bss = 0L;
    brk = 0L;

    for(i=0; i<num; i++){
        unsigned long size, offset;
        unsigned long prot, flags;
        unsigned long base, vaddr;

        if(lpPhdr[i].p_type == PT_INTERP){
            printf("ElfLoader does not implement PT_INTERP type\n");
            continue;
        }
        if(lpPhdr[i].p_type != PT_LOAD){continue;}
        prot = 0;
        if(lpPhdr[i].p_flags & PF_R){ prot |= PROT_READ;}
        if(lpPhdr[i].p_flags & PF_W){ prot |= PROT_WRITE;}
        if(lpPhdr[i].p_flags & PF_X){ prot |= PROT_EXEC;}
        
        flags = MAP_PRIVATE | MAP_FIXED;        
        base = lpPhdr[i].p_vaddr;
        size = lpPhdr[i].p_filesz;
        offset = lpPhdr[i].p_offset;
        map_addr = (void*)MemoryMap(fd, (PAGE_START(base)), (size+PAGE_OFFSET(base)), prot, flags, offset-PAGE_OFFSET(base));
        if(map_addr == MAP_FAILED){
            printf("ElfLoader : MmeoryMap failed addr=%p\n", map_addr);
            return -1;
        }
        vaddr = lpPhdr[i].p_vaddr;
        if(vaddr < startCodeAddr){
	  startCodeAddr = vaddr;
        }
        vaddr = lpPhdr[i].p_vaddr+lpPhdr[i].p_filesz;
        if(vaddr > bss){
            bss = vaddr;
        }
        if((lpPhdr[i].p_flags & PF_X) && (endCodeAddr < vaddr)){
            endCodeAddr = vaddr;
        }
        if((lpPhdr[i].p_flags & PF_W) && (lpPhdr[i].p_vaddr < startDataAddr)){
            startDataAddr = lpPhdr[i].p_vaddr;
        }
        if(endDataAddr < vaddr){
            endDataAddr = vaddr;
        }
        vaddr = lpPhdr[i].p_vaddr + lpPhdr[i].p_memsz;
        if(vaddr > brk){
            brk = vaddr;
        }
    }

    lpPi->startCodeAddr = startCodeAddr;
    lpPi->endCodeAddr = endCodeAddr;
    lpPi->startDataAddr = startDataAddr;
    lpPi->endDataAddr = endDataAddr;
    lpPi->bssStartAddr = bss;
    lpPi->bssEndAddr = brk;
    lpPi->brk = PAGE_ALIGN(brk);
    return 1;
}

static int MapBssSection(ProcessInfo *lpPi)
{
    unsigned long start, end;	
    unsigned long prot, flags;
    void *map_addr;
	
    start = PAGE_ALIGN(lpPi->bssStartAddr);
    end = PAGE_ALIGN(lpPi->bssEndAddr);

    if(end > start){
        map_addr = NULL;
        flags = MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS;
        prot = PROT_READ | PROT_WRITE;
        map_addr = (void*)MemoryMap(-1, start, end-start, prot, flags, 0);
        if(map_addr == MAP_FAILED){
            return -1;
        }
        memset((void*)lpPi->bssStartAddr, 0, lpPi->bssEndAddr - lpPi->bssStartAddr);
    }
    return 1;
}

#define PUSH(sp, val) \
    sp--;\
    *sp = (unsigned long)(val);

static int CreateElfTables(LoaderArg *lpArgs, ProcessInfo *lpPi)
{
    int i, len;
    unsigned long *sp;

    sp = (unsigned long*)lpPi->stackCurAddr;
    /* setup linux args */
    {
        unsigned long *sbase;
        sbase = (unsigned long*)(lpPi->stackCurAddr+1);
        /* env */
        PUSH(sp, NULL);
        PUSH(sp, NULL);
        /* arg */
        PUSH(sp, NULL);
        if(lpArgs->argv != NULL){
            for(i=0; i<lpArgs->argc; i++){
                PUSH(sp, sbase);
                len = strlen((char *)sbase);
                sbase = (unsigned long*)((char*)sbase + len+1);
            }
        }
        PUSH(sp, lpArgs->argc);
    }
    lpPi->stackCurAddr = (unsigned long)sp;
    return 1;
}
#undef PUSH

static unsigned long _entry, _sp;

static int LoadElfExec(int fd, LoaderArg *lpArgs, Ehdr *lpEhdr, Phdr *lpPhdr)
{
    ProcessInfo *lpPi;
   
    /* mmap programs */
    lpPi = GetProcessInfo();
    if( MapElfProgram(fd, lpPhdr, lpEhdr->e_phnum, lpPi) < 0){
        return -1;
    }
    if( MapBssSection(lpPi) < 0){
        return -1;
    }
    if(CreateStackArea(lpArgs, lpPi) < 0){
        printf("CreateStackArea failed \n");
        return -1;
    }

#ifdef DEBUG
	ShowProcessInfo();
#endif

    if(CreateElfTables(lpArgs, lpPi) < 0){
        printf("CreateElfTables failed\n");
        return -1;
    }
    _entry = lpEhdr->e_entry;
    _sp = lpPi->stackCurAddr;

    close(fd);
    FreeElfProgramHeader(lpPhdr);

    PrintProcessInfo(lpPi);
    printf("--------------exec start----------------\n");
    ptrace(PTRACE_TRACEME, 0, 0, 0);
    kill(getpid(), SIGSTOP);
    EXECUTE_BINARY(_entry, _sp);
    printf("---------------exec end-----------------\n");
    return 1;
}


/**********************************************************************************
 *
 * core
 *
 **********************************************************************************/
static LinkedList *ReadElfCoreNote(int fd, Phdr *lpPhdrTypeNote);
static void FreeNoteList(LinkedList *list);
static int RestoreNote(LinkedList *list, int type, void* buf);
static int MapElfCoreProgram(int fd, const Phdr *pheader, int num);
static int LoadElfProgramCodeArea(char *prog, ProcessInfo *pi);
static int LoadElfCore(int fdd, LoaderArg *lpArgs, Ehdr *lpEhdr, Phdr *lpPhdr);

static struct user_regs_struct regs;

#ifdef __DEBUG__
static void PrintUserRegs(struct user_regs_struct *r)
{
    printf("\n");
    printf("regs\n");
    printf(" eax[0x%08lx] ebx[0x%08lx]\n", r->eax, r->ebx);
    printf(" ecx[0x%08lx] ecx[0x%08lx]\n", r->ecx, r->edx);
    printf(" esi[0x%08lx] edi[0x%08lx]\n", r->esi, r->edi);
    printf(" ebp[0x%08lx] esp[0x%08lx]\n", r->ebp, r->esp);
    printf(" eip[0x%08lx]\n", r->eip);
    printf(" orig_eax[0x%08lx]\n", r->orig_eax);
}
#endif

static LinkedList *ReadElfCoreNote(int fd, Phdr *lpPhdrTypeNote)
{
    char *buf;
    Phdr *lpPhdr;
    int nheaderNum;
    Nhdr *lpNhdr;
    LinkedList *list;

    lpPhdr = lpPhdrTypeNote;
    {
        if(lseek(fd, lpPhdr->p_offset, SEEK_SET) != lpPhdr->p_offset){
            perror("lseek");
        }
        buf = (char*)malloc(sizeof(char)*lpPhdr->p_filesz);
        if(read(fd, buf, lpPhdr->p_filesz) < 0){
            perror("read");
        }
    }
    {
        int pos;
        pos=0;
        nheaderNum = 0;
        while(pos < lpPhdr->p_filesz){
            lpNhdr = (Nhdr*)(buf+pos);
            pos += sizeof(Nhdr) + lpNhdr->n_namesz + lpNhdr->n_descsz;
            nheaderNum++;
        }
    }
    {
        Note *tmp;
        int pos, i;

        list = NewLinkedList();
        pos=0;
        for(i=0; i<nheaderNum; i++){
            tmp = (Note*)malloc(sizeof(Note));
            lpNhdr = (Nhdr*)(buf+pos);
            pos += sizeof(Nhdr);
            if( strncmp(buf+pos, "CORE", 4)!=0){
                FreeNoteList(list);
                return NULL;
            }
            tmp->type = lpNhdr->n_type;
            tmp->datasize = lpNhdr->n_descsz;
            tmp->data = (char*)malloc(sizeof(char)*lpNhdr->n_descsz);
            memcpy((void*)tmp->data, (void*)(buf+pos+(int)lpNhdr->n_namesz), lpNhdr->n_descsz);
            AddLinkedListItem(list, tmp);
            pos += lpNhdr->n_namesz + lpNhdr->n_descsz;
        }
    }
    free(buf);
    return list;
}

static void FreeNoteList(LinkedList *list)
{
    int i;
    Note *note;
    for(i=0; i<GetLinkedListSize(list); i++){
        note = (Note*)GetLinkedListItem(list, i);
        if(note != NULL){
            free(note);
        }
    }
    DeleteLinkedList(list);
}

static int RestoreNote(LinkedList *list, int type, void* buf)
{
    int i;
    for(i=0; i<GetLinkedListSize(list); i++){
        Note *note;
        note = (Note*)GetLinkedListItem(list, i);
        if(note->type == type){
            memcpy(buf, note->data, note->datasize);
            return 1;
        }
    }
    return -1;
}

static int MapElfCoreProgram(int fd, const Phdr *pheader, int num)
{
    void *map_addr;
    unsigned long prot, flags;
    unsigned long base, size, offset;
    int i;
    
    for(i=0; i<num; i++){
        if(pheader[i].p_type == PT_INTERP){
            continue;
        }
        if(pheader[i].p_type != PT_LOAD){ continue; }
    	prot = 0;
        if(pheader[i].p_flags & PF_R){ prot |= PROT_READ;}
        if(pheader[i].p_flags & PF_W){ prot |= PROT_WRITE;}
        if(pheader[i].p_flags & PF_X){ prot |= PROT_EXEC;}
        
        flags = MAP_PRIVATE | MAP_FIXED;
        base = pheader[i].p_vaddr;
        size = pheader[i].p_filesz;
        offset = pheader[i].p_offset;
        map_addr = (void*)MemoryMap(fd, PAGE_START(base), size+PAGE_OFFSET(base), prot, flags, offset-PAGE_OFFSET(base));
        if(map_addr == MAP_FAILED){
            return -1;
        }
    }
    return 1;
}


//map text
static int LoadElfProgramCodeArea(char *prog, ProcessInfo *pi)
{
    int fd;
    Ehdr progHdr;
    {
        fd = open(prog, O_RDONLY , 0);
        if(fd < 0){
            return -1;
        }
    }
    
    {
        Phdr *lpProgPhdr;
        char buf[128];
	int i;
        
        if(read(fd, buf, sizeof(buf)) < 0){
            perror("read");
            goto lferr;
        }
        
        if(CheckElfBinary(buf, sizeof(buf))<0){
            goto lferr;
        }
        if(ReadHeader(fd, &progHdr) < 0){
            goto lferr;
        }
        if((lpProgPhdr = ReadElfProgramHeader(fd, &progHdr)) == NULL){
            goto lferr;
        }
        for(i=0; i<progHdr.e_phnum; i++){
            unsigned long prot, flags;
            unsigned long base, size, offset;
            void *map_addr;
            if(lpProgPhdr[i].p_type == PT_INTERP){
                continue;
            }
            if(lpProgPhdr[i].p_type != PT_LOAD){ continue; }
            prot = 0;
            if(lpProgPhdr[i].p_flags & PF_R){ prot |= PROT_READ;}
            if(lpProgPhdr[i].p_flags & PF_W){ prot |= PROT_WRITE;}
            if(lpProgPhdr[i].p_flags & PF_X){ prot |= PROT_EXEC;}
            
            if(lpProgPhdr[i].p_flags & PF_X){
                flags = MAP_PRIVATE | MAP_FIXED;
                base = lpProgPhdr[i].p_vaddr;
                size = lpProgPhdr[i].p_filesz;
                offset = lpProgPhdr[i].p_offset;
                map_addr = (void*)MemoryMap(fd, PAGE_START(base), size+PAGE_OFFSET(base), prot, flags, offset-PAGE_OFFSET(base));
                if(map_addr == MAP_FAILED){
                    FreeElfProgramHeader(lpProgPhdr);
                    goto lferr;
                }
            }
        }
        FreeElfProgramHeader(lpProgPhdr);
    }
    close(fd);
    return 1;
lferr :
    close(fd);
    return -1;
}

static int LoadElfCore(int fd, LoaderArg *lpArgs, Ehdr *lpEhdr, Phdr *lpPhdr)
{
    LinkedList *list;
    struct user proc_user;
    ProcessInfo processInfo;
    struct user_desc tlsInfo;

    list = ReadElfCoreNote(fd, lpPhdr);
    if(list == NULL){
        return -1;
    }
    
    if(RestoreNote(list, NT_PRXREG, &proc_user) < 0){ return -1;}
    if(RestoreNote(list, NT_PROCESSINFO, &processInfo) < 0){ return -1;}
#ifdef __NR_set_thread_area
    printf("Ryo: set do something about tls!\n");
    fflush( stdout );
    if( !(RestoreNote(list, NT_TLSINFO, &tlsInfo) < 0) ){
        tlsInfo.entry_number = 6+1;
        printf("tlsInfo.base_addr: %08lx\n", tlsInfo.base_addr);
        if(SysCallSetThreadArea(&tlsInfo) < 0){
            perror("set_thread_area");
            return -1;
        }
    }
#endif

    SetProcessInfo(&processInfo);
    //map program
    if(LoadElfProgramCodeArea(processInfo.progname, &processInfo) < 0){
      goto lfcerr;
    }
    //map core
    if(MapElfCoreProgram(fd, lpPhdr, lpEhdr->e_phnum) < 0){
        goto lfcerr;
    }
    FreeElfProgramHeader(lpPhdr);
    FreeNoteList(list);
    close(fd);

    memcpy(&regs, &(proc_user.regs), sizeof(regs));
    
#ifdef __DEBUG__
    PrintUserRegs(pregs);
#endif

    printf("--------------exec start----------------\n");
    ptrace(PTRACE_TRACEME, 0, 0, 0);
    kill(getpid(), SIGSTOP);
#ifdef __NR_set_thread_area
    TLS_SET_GS(tlsInfo.entry_number*8+3);
#endif
    EXECUTE_CORE(regs);
    return 1;    
lfcerr:
    FreeNoteList(list);
    return -1;
}

/**********************************************************************************
 *
 * symbol 
 *
 **********************************************************************************/
/*
#define LABEL_INDEX (8)
unsigned char code[] =
{
    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, //jmp xxxxxxxx
    0x90,
    0x00, 0x00, 0x00, 0x00	//jmp label
};

static Sym* _lpSymbolTable;
static int _SymbolNum;
static char *_lpSymbolStrTable;

static int SearchSymbol(char *name, Sym *dst)
{
    Sym *sym;
    int i, len;

    len = strlen(name);
    for(i=0; i<_SymbolNum; i++){
        if(strncmp(name, (char*)(_lpSymbolStrTable+_lpSymbolTable[i].st_name), len)==0){
            sym = (Sym*)(_lpSymbolTable+i);
            memcpy(dst, sym, sizeof(Sym));
            return 1;
        }
    }
    printf("symbol:%s nod found\n", name);
    return -1;
}

static int GetSymbolHeader(const int fd, Ehdr *lpEhdr, Shdr *lpSymShdr)
{   
    int i;
    lseek(fd, lpEhdr->e_shoff, SEEK_SET);
    for(i=0; i<lpEhdr->e_shnum; i++){
        read(fd, lpSymShdr, sizeof(Shdr));
        if(lpSymShdr->sh_type == SHT_SYMTAB){
            return 1;
        }
    }
    lpSymShdr = NULL;
    return -1;
}

static int InitializeElfSymbol(const int fd, Ehdr *lpEhdr)
{
    Shdr SymShdr, SymStrShdr;
    char *strbuf, *buf;
    
    if(GetSymbolHeader(fd, lpEhdr, &SymShdr) < 0){
        printf("no symbol\n");
        return -1;
    }
    lseek(fd, lpEhdr->e_shoff+(SymShdr.sh_link*sizeof(Shdr)), SEEK_SET);
    read(fd, &SymStrShdr, sizeof(Shdr));
    
    //symbol table
    buf = (char*)mAlloc(sizeof(char)*(SymShdr.sh_size));
    lseek(fd, SymShdr.sh_offset, SEEK_SET);
    read(fd, buf, SymShdr.sh_size);
    
    //Symbol string table
    strbuf = (char*)mAlloc(sizeof(char)*SymShdr.sh_size);
    lseek(fd, SymStrShdr.sh_offset, SEEK_SET);
    read(fd, strbuf, SymShdr.sh_size);

    _SymbolNum = SymShdr.sh_size / sizeof(Sym);
    _lpSymbolTable = (Sym*)buf;
    _lpSymbolStrTable = strbuf;

    return 1;
}

static int FinalizeElfSymbol(void)
{
    _SymbolNum = 0;
    free(_lpSymbolTable);
    free(_lpSymbolStrTable);
    return 1;
}
*/
/*
static int ElfHookFucntion(char *hookfuncname, unsigned long hookfuncaddr)
{
    MemMapInfo *tmp;
    unsigned char *c;
    int flags;
    Sym sym;
    
    if(hookfuncname == NULL){
        printf("hookfuncname nullp\n");
        return -1;
    }
    
    if(SearchSymbol(hookfuncname, &sym) < 0){
        return -1;
    }
    tmp = GetMemoryRegion(memInfoList, sym->st_value);
    if(tmp == NULL){
        return -1;
    }
    
    c = (unsigned char*)strdup((char *)code);
    (*(unsigned int*)(c+LABEL_INDEX)) = hookfuncaddr;
    c[2] = (unsigned char)(((int)(c+LABEL_INDEX) >> 0) & 0xff);
    c[3] = (unsigned char)(((int)(c+LABEL_INDEX) >> 8) & 0xff);
    c[4] = (unsigned char)(((int)(c+LABEL_INDEX) >> 16) & 0xff);
    c[5] = (unsigned char)(((int)(c+LABEL_INDEX) >> 24) & 0xff);
    
    mprotect((void*)tmp->start, tmp->end-tmp->start, PROT_EXEC | PROT_READ | PROT_WRITE);
    memcpy((void*)sym->st_value, c, 11);
    if(tmp->flags & PF_R){ flags |= PROT_READ; }
    if(tmp->flags & PF_W){ flags |= PROT_WRITE; }
    if(tmp->flags & PF_X){ flags |= PROT_EXEC;}
    mprotect((void*)tmp->start, tmp->end-tmp->start, flags);

    free(c);
    return 1;

}
*/

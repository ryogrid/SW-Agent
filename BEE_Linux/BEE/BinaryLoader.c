#include "inc.h"

static LoaderFunction **loaderList;
static unsigned int loaderSize;

static int RegisterLoader(LoaderFunction* lf);
static LoaderFunction *SearchLoader(const int fd);

int InitLoader(void)
{
    loaderList = NULL;
    loaderSize = 0;
    
    if(RegisterLoader(GetElfLoaderFunction()) <0){return -1;}

    return 1;
}

static int RegisterLoader(LoaderFunction* lf)
{    
    if(lf == NULL){
        return -1;
    }
    loaderList = (LoaderFunction**)reAlloc(loaderList, sizeof(LoaderFunction*)*(loaderSize+1));
    loaderList[loaderSize] = lf;
    loaderSize++;
    return 1;
}

static LoaderFunction *SearchLoader(const int fd)
{
    int i;
    char buf[128];

    if(read(fd, buf, sizeof(buf))<0){
        printf("searchLoader : read error\n");
        return NULL;
    }

    for(i=0; i<loaderSize; i++){
        if(loaderList[i]->check(buf, sizeof(buf))>0){
            return loaderList[i];
        }
    }
    return NULL;
}

int LoadBinary(const char *program, LoaderArg *args)
{
    LoaderFunction *lf;
    int fd;

    //    printf("%s program loads \n", program);
    fd = open(program, O_RDONLY);
    if(fd < 0){
        printf("SearchLoader : open error '%s'\n", program);
        return -1;
    }
    
    lf = SearchLoader(fd);
    if(lf == NULL){
        printf("SearchLoader : program format not found\n");
        close(fd);
        return -1;
    }

    if(lf->load(fd, args)<0){
        printf("Loader : program loads error\n");
        close(fd);
        return -1;
    }
//  close(fd);
    return 1;
}

#define MAX_ARG_PAGES (64)

int CreateStackArea(LoaderArg *args, ProcessInfo *pi)
{
    unsigned long stackBase, stackAddr, stackSize;
    int i, len;

    if(args == NULL || pi == NULL){
        return -1;
    }
    stackSize = MAX_ARG_PAGES*PAGE_SIZE;

    {
        void *mmap_addr;
        unsigned long prot, flags;
        stackBase = STACK_TOP_ADDR - (MAX_ARG_PAGES*PAGE_SIZE);
        flags = MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS;
        prot = PROT_READ | PROT_WRITE;
        //mmap_addr = (void*)MemoryMap(NULL, stackBase, stackSize, prot, flags, 0);
        mmap_addr = (void*)MemoryMap(-1, stackBase, stackSize, prot, flags, 0);
        if(mmap_addr == MAP_FAILED){
            return -1;
        }
        memset(mmap_addr, 0, stackSize);
    }
    
    stackAddr = STACK_TOP_ADDR-4;
#if 0
    for(i=0; i<args->envc; i++){
        len = strlen(args->envp[i]);
        stackAddr -= len+1;
        strncpy((void*)stackAddr, args->envp[i], len+1);
    }
    args->envTopAddr = (void*)stackAddr;
#else
    args->envp = NULL;
    args->envc = 0;
    args->envp = NULL;
#endif
    
    for(i=0; i<args->argc; i++){
        len = strlen(args->argv[i]);
        stackAddr -= len+1;
        memcpy((void*)stackAddr, args->argv[i], len+1);
    }
    
    pi->stackTopAddr = STACK_TOP_ADDR;
    pi->stackSize = stackSize;
    pi->stackCurAddr = stackAddr-1;
    return 1;
}

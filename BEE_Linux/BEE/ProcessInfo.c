#include "inc.h"

static ProcessInfo pi;

int InitProcessInfo(char *progname)
{
    memset(&pi, 0, sizeof(ProcessInfo));
    memcpy(pi.progname, progname, sizeof(pi.progname));
    return 1;
}

int FinalizeProcessInfo()
{
    return 1;
}

ProcessInfo *GetProcessInfo()
{
    return &pi;
}

void SetProcessInfo(ProcessInfo *_pi)
{
    memset(pi.progname, 0, sizeof(pi.progname));
    memcpy(pi.progname, _pi->progname, sizeof(pi.progname));
    pi.startCodeAddr    = _pi->startCodeAddr;
    pi.endCodeAddr      = _pi->endCodeAddr;
    pi.startDataAddr    = _pi->startDataAddr;
    pi.endDataAddr      = _pi->endDataAddr;
    pi.bssStartAddr     = _pi->bssStartAddr;
    pi.bssEndAddr       = _pi->bssEndAddr;
    pi.stackTopAddr     = _pi->stackTopAddr;
    pi.stackCurAddr     = _pi->stackCurAddr;
    pi.stackSize        = _pi->stackSize;
    pi.brk              = _pi->brk;
}

char *GetProgramName(void)
{
    return pi.progname;
}

void PrintProcessInfo(ProcessInfo *pi)
{
    printf("addr %p %d\n", pi, sizeof(ProcessInfo)); 
    printf("prog:(%p)%s\n", pi->progname, pi->progname);
    printf("code:[%08lx(%p)-%08lx]\n", pi->startCodeAddr,&pi->startCodeAddr, pi->endCodeAddr);
    printf("data:[%08lx(%p)-%08lx]\n", pi->startDataAddr, &pi->startDataAddr, pi->endDataAddr);
    printf("bss:[%08lx-%08lx]\n", pi->bssStartAddr, pi->bssEndAddr);
    printf("stack:%08lx size:%08lx sp:%08lx\n", pi->stackTopAddr, pi->stackSize, pi->stackCurAddr);
    printf("brk:%08lx\n", pi->brk);
}

#include "inc.h"

int (*SystemCallsTable[NR_syscalls])();

static int SysCallDummy(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int eax)
{
    printf("sysdummy %d [ %s ]\n", eax,SystemCallsName[eax]);
    return -1;
}

/* execute system call directly */
static int SysCallDirect()
{
  asm(
    "int $0x80"
      );
}

void InitSystemCalls()
{
    int i;
    for(i=0; i<NR_syscalls; i++){
/*       SystemCallsTable[i] = NULL; */
      SystemCallsTable[i] = SysCallDummy;
    }
    SystemCallsTable[__NR_exit]     = exit;
    SystemCallsTable[__NR_getpid]   = getpid;
    SystemCallsTable[__NR_uname]    = uname;

/*     SystemCallsTable[__NR_write]    = write; */
    SystemCallsTable[__NR_write]    = SysCallWrite;

    /* added by Ryo for video_capture - Start -*/
/*     SystemCallsTable[__NR_open]    = open; */
    SystemCallsTable[__NR_open]    = SysCallOpen;

/*     SystemCallsTable[__NR_ioctl]    = ioctl; */
    SystemCallsTable[__NR_ioctl]    = SysCallIoctl;
    SystemCallsTable[__NR_close]    = close;
    SystemCallsTable[__NR_rt_sigaction]    = sigaction;
    SystemCallsTable[__NR_sigaction]    = sigaction;
    SystemCallsTable[__NR_signal]    = signal;
    SystemCallsTable[__NR_setitimer]    = setitimer;
    SystemCallsTable[__NR_gettimeofday]    = gettimeofday;
    SystemCallsTable[__NR_read]    = read;
    SystemCallsTable[__NR_clock_gettime]    = clock_gettime;
    SystemCallsTable[__NR_clock_getres]    = clock_getres;
    SystemCallsTable[__NR_dup]    = dup;
/*     SystemCallsTable[__NR_socketcall]    = socket; */
    SystemCallsTable[__NR_socketcall]    = SysCallDirect;
    SystemCallsTable[__NR_fcntl64]    = fcntl;
/*     SystemCallsTable[__NR__llseek]    = lseek; */
    SystemCallsTable[__NR__llseek]    = SysCallDirect;
    SystemCallsTable[__NR_fstat64]    = fstat;

    SystemCallsTable[__NR_getuid32]    = getuid;
    SystemCallsTable[__NR_geteuid32]    = geteuid;

    SystemCallsTable[__NR_access]    = access;

    SystemCallsTable[__NR_set_thread_area]      = SysCallSetThreadArea;

    SystemCallsTable[__NR__newselect]      = SysCallDirect;
    /* end of entries added by Ryo */

    SystemCallsTable[__NR_brk]      = SysCallBrk;

    /* for pipe -Start- */
    SystemCallsTable[__NR_mprotect] = SysCallDirect;
/*     SystemCallsTable[__NR_mknod] = SysCallDirect; */
    /* for pipe -End -* /

    /* added by Ryo -End-*/

/*     SystemCallsTable[__NR_mmap]	    = mmap; */
    SystemCallsTable[__NR_mmap]	    = SysCallMmap; /* by Ryo */
/*     SystemCallsTable[__NR_mmap2]    = SysCallDirect; */
    SystemCallsTable[__NR_mmap2]    = SysCallMmap; /* by Ryo */
    SystemCallsTable[__NR_munmap]   = munmap;

    /* comment outed by Ryo*/
    /* this make function of process migration disabled*/
/*     SystemCallsTable[__NR_mmap]	    = SysCallMemoryMap; */
/*     SystemCallsTable[__NR_mmap2]    = SysCallMemoryMap2; */
/*     SystemCallsTable[__NR_munmap]   = SysCallMemoryUnmap; */

#ifdef __NR_set_thread_area
    SystemCallsTable[__NR_set_thread_area]      = SysCallSetThreadArea;
#endif

}

#define _GNU_SOURCE
#include "inc.h"

static void PrintUsage()
{
    printf("Usage: exec program [args] \n");
    exit(1);
}

static int Initialize(char *progname)
{
    if(InitLoader()<0){
        printf("loader initialization is error\n");
        return -1;
    }
    InitBeeMemory();
    InitSystemCalls();
    if(InitProcessInfo(progname)<0){ return -1; }

    if(mmap((void*)0x70000000, 0xb7fff000-0x70000000,
	    PROT_READ,
	    MAP_NORESERVE  | MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS,
	    -1, 0) == MAP_FAILED){
        perror("mmap");
        return -1;
    }
    return 1;
}

#define DUMP_EXT "core"

static pid_t pid;

#include <sys/time.h>
#include <unistd.h>

double
second(void)
{
  struct timeval tm;
  double t;
  gettimeofday(&tm, NULL);
  t = (double)(tm.tv_sec) + ((double)(tm.tv_usec))/1.0e6;
  return t;
}

static void SigDumpElfCore(int sig)
{
    char *dumpname;
    double start,end;
    ProcessInfo pi;

    printf("\n");
    printf("dump process image pid:%d\n", pid);
    start = second();
    /*
    if(kill(pid, SIGSTOP) < 0){
        perror("kill");
        ptrace(PTRACE_KILL, pid, NULL, NULL);
        exit(1);
    }
    printf("wait\n");
    wait(NULL);
    */
    printf("read\n");
    if(ReadProcessInfoMemory(pid, &pi) < 0){
        printf("ReadProcessInfoMemory failed\n");
        goto sig_err;
    }
    printf("dump");
    dumpname = (char*)mAlloc(sizeof(char)*(strlen(pi.progname)+strlen(DUMP_EXT)+2));
    sprintf(dumpname, "%s.%s", pi.progname, DUMP_EXT);
    printf("'%s'\n", dumpname);
    if(DumpElfCoreFile(pid, dumpname)<0){
    	printf("dump err\n");
    }
 sig_err:
    ptrace(PTRACE_KILL, pid, NULL, NULL);
    end = second();
    printf("elapsed time %f s\n", end-start);
    exit(1);
}

void printregs(struct user_regs_struct regs)
{
    printf("orig_eax[%08lx] eax[%08lx] eip[%08lx]\n", regs.orig_eax, regs.eax, regs.eip);
    printf("ebx[%08lx] ecx[%08lx] edx[%08lx]\n", regs.ebx, regs.ecx, regs.edx);
    printf("esi[%08lx] edi[%08lx]\n", regs.esi, regs.edi);
    printf("ebp[%08lx] esp[%08lx]\n", regs.ebp, regs.esp);
    printf("gs[%08x]\n", regs.gs);

}

void blockSignal(int block)
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    if(sigprocmask( (block ? SIG_BLOCK: SIG_UNBLOCK), &sigset, NULL) < 0){
        perror("sigprocmask");
        exit(1);
    }
}

void main_loop()
{
    int status;
    struct user_regs_struct regs;
    ProcessInfo pi;
    int sys_emu;
    unsigned long tmp_orig_eax, orig_eax;

    sys_emu = 0;
    tmp_orig_eax = 0;
    orig_eax = 0;

    int sig = 0;

    if(ReadProcessInfoMemory(pid, &pi) < 0){
        printf("ReadProcessInfoMemory\n");
        ptrace(PTRACE_KILL, pid, NULL, NULL);
        exit(1);
    }
    while(1){
        if(ptrace(PTRACE_SYSCALL, pid, 0,sig) == -1){
            perror("ptrace1");
            break;
        }
	sig = 0;

        wait(&status);
        if(WIFEXITED(status)){
            printf("WIFEXITED\n");
            break;
        }
        if(WIFSTOPPED(status)){
            if(WSTOPSIG(status) == SIGSEGV){
                ptrace(PTRACE_GETREGS, pid, 0, &regs);
                printf("SIGSEGV\n");
                printregs(regs);
                break;
            }else if(WSTOPSIG(status) != SIGTRAP){
	      /* added by Ryo */
	      sig = WSTOPSIG(status);
//	      printf("passing %d signal to child\n",sig);
/* 	      if(sig == 13){ */
/* 		sig = 0; */
/* 	      } */
	    }
        }
        ptrace(PTRACE_GETREGS, pid, 0, &regs);
	/* added by Ryo */
	#ifdef DEBUGLOG
	printf("emulate %s [orig_eax = %ld][eax = %ld]\n",SystemCallsName[regs.orig_eax],regs.orig_eax,regs.eax);
	printregs(regs);
	#endif
        tmp_orig_eax = regs.orig_eax;
/*  for avoiding stop when sigpipe occurs */
/*         if(tmp_orig_eax == -1){ */
/*             printf("PTRACE_SYSCALL error\n"); */
/*             printregs(regs); */
/*             break; */
/*         } */

        //system call enter
        if( (sys_emu == 0) && (SystemCallsTable[tmp_orig_eax] != NULL) &&
            (regs.eip >= pi.startCodeAddr) && (regs.eip < pi.endCodeAddr)){
	  //blockSignal(1);

/* 	  if(tmp_orig_eax != 142){ /\* pass select() *\/ */
	    sys_emu = 1;
	    orig_eax = regs.orig_eax;//save orig_eax
	    regs.orig_eax = LONG_MAX;
	    /* 	  regs.gs = 0x33; 	/\* added by Ryo *\/ */
/* 	  } */

	  if(ptrace(PTRACE_SETREGS, pid, 0, &regs) == -1){
	    perror("ptrace2");
	    break;
	  }

        }
        //systemcall leave
        else if(sys_emu == 1){
            unsigned long orig_eip;
            sys_emu = 0;

            regs.eax = orig_eax;
            regs.orig_eax = orig_eax; //restore orig_eax

	      orig_eip = regs.eip;
	      regs.eip = (unsigned long)_SystemCallHandle;
	      regs.esp -= 4;
/* 	      regs.gs = 0x33; 	/\* added by Ryo *\/ */
	      if(WriteProcessMemory(pid, (void*)regs.esp, (void*)orig_eip, sizeof(orig_eip)) < 0){
                printf("WriteProcessMemory\n");
                break;
	      }

            if(ptrace(PTRACE_SETREGS, pid, 0, &regs) == -1){
                perror("ptrace3");
                break;
            }
	    //            blockSignal(0);
        }
    }
    return;
}

int main(int argc, char **argv, char **envp)
{
    if(argc == 1){
        PrintUsage();
        exit(0);
    }
    if(Initialize(argv[1]) < 0){
    	exit(1);
    }

    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        LoaderArg args;
        int i;
        char **p;

        memset(&args, 0, sizeof(LoaderArg));
        p = (char **)mAlloc(sizeof(char*)*(argc-1));
        for(i=1; i<argc; i++){ p[i-1] = argv[i];}
        args.argc = argc-1;
        args.argv = p;

        if(signal(SIGINT, SIG_IGN) < 0){
            perror("signal");
            exit(1);
        }
        if(LoadBinary(GetProgramName(), &args)<0){
            printf("loader loads failed '%s'\n", GetProgramName());
            exit(1);
        }
        exit(0);
    }
    else{
        struct sigaction sa;

        memset(&sa, 0, sizeof(sa));
/*         disabled process dump by Ryo              */
/*         sa.sa_handler = SigDumpElfCore; */
/*         sa.sa_flags = SA_RESETHAND | SA_SIGINFO | SA_RESTART ; */
/*         sigaction(SIGINT, &sa, NULL); */
        wait(NULL);//for SIGSTOP
        main_loop();
        ptrace(PTRACE_KILL, pid, NULL, NULL);
    }
    return 0;
}

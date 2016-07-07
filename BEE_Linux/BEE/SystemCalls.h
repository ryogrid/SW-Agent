#ifndef SYSTEMCALLS_H_
#define SYSTEMCALLS_H_

#include "inc.h"

#ifndef NR_syscalls
# define NR_syscalls 318
#endif

void InitSystemCalls();
int _SystemCallHandle();
//global
//int (*SystemCallsTable[NR_syscalls])(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
int (*SystemCallsTable[NR_syscalls])();
char *SystemCallNameTable[NR_syscalls];

#endif /*SYSTEMCALLS_H_*/

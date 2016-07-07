#ifndef PROCESSINFO_H_
#define PROCESSINFO_H_

#include "inc.h"

#ifndef PAGE_SIZE
# define PAGE_SIZE (0x1000)
#endif

#ifndef PAGE_START
# define PAGE_START(_v) ( (_v) & ~(PAGESIZE-1))
#endif

#ifndef PAGE_ALIGN
# define PAGE_ALIGN(_v) (((_v) + PAGESIZE-1) & ~(PAGESIZE-1))
#endif

#ifndef PAGE_OFFSET
# define PAGE_OFFSET(_v) ((_v) & (PAGESIZE-1))
#endif

int InitProcessInfo(char *progname);
int FinalizeProcessInfo(void);

ProcessInfo *GetProcessInfo(void);
void SetProcessInfo(ProcessInfo *_pi);

char *GetProgramName(void);
void PrintProcessInfo(ProcessInfo *pi);

#endif /*PROCESSINFO_H_*/

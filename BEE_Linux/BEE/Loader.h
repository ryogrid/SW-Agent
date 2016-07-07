#ifndef LOADER_H_
#define LOADER_H_

#include "inc.h"

typedef struct _LoaderArgument
{
    int  argc, envc;
    char **argv;
    char **envp;
} LoaderArg;

typedef struct _LoaderFunction
{
    int (*load)(int fd, LoaderArg *lpArgs);
    int (*check)(char *buf, unsigned int size);
} LoaderFunction;

int InitLoader(void);
int LoadBinary(const char *program, LoaderArg *args);

/* stack */
int CreateStackArea(LoaderArg *args, ProcessInfo *pi);

/* define prototype of ELF binary loader function */
LoaderFunction *GetElfLoaderFunction(void);

#endif /*LOADER_H_*/

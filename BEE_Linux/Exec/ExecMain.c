#include "inc.h"

#ifndef ADDR_NO_RANDOMIZE    /* disable randomization of VA space */
# define ADDR_NO_RANDOMIZE 0x0040000
#endif
#ifndef ADDR_COMPAT_LAYOUT
# define ADDR_COMPAT_LAYOUT 0x0200000
#endif

#define BEE_EXEC "./BEE"

int main(int argc, char **argv)
{
    if(argc == 1){
        return 0;
    }
    
    argv[0] = BEE_EXEC;
    personality(ADDR_NO_RANDOMIZE | personality(-1));

    if(execvp(BEE_EXEC, argv) < 0){
        perror("exec");
    }
    exit(0);
    return 0;
}


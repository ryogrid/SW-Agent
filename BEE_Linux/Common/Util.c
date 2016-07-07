#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util.h"

void *mAlloc(unsigned int size)
{
    void *mp;
    mp = malloc(size);
    if(mp == NULL){
        printf("Out of Memory error\n");
        exit(1);
    }
    memset(mp, 0, size);
    return mp;
}

void *reAlloc(void *ptr, unsigned int size)
{
    void *mp;
    mp = realloc(ptr, size);
    if(mp == NULL){
        printf("Out of Memory error\n");
        exit(1);
    }
    return mp;
}

char *endWith(char *str, char c)
{
    int len, i;

    len = strlen(str);
    for(i=len-1; i>=0; i--){
        if(str[i]==c){
            i++;
            return (char*)(str+i);
        }
    }
    return NULL;
}

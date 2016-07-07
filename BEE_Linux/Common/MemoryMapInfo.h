#ifndef _COM_MMAPINFO_H_
#define _COM_MMAPINFO_H_

#pragma pack(1)

typedef struct _MemMapInfo
{
    unsigned long start, end;
    char *pathname;
    int flags;
    struct _MemMapInfo *next;
} MemMapInfo;

#pragma pack()


#endif

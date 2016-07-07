#ifndef _COM_SYSTEM_INFO_H_
#define _COM_SYSTEM_INFO_H_

#define STACK_TOP_ADDR (0x70000000)
#define STACK_PAGE (32)

/*
typedef struct modify_ldt_ldt_s
{
    unsigned int  entry_number;
    unsigned long base_addr;
    unsigned int  limit;
    unsigned int  seg_32bit:1;
    unsigned int  contents:2;
    unsigned int  read_exec_only:1;
    unsigned int  limit_in_pages:1;
    unsigned int  seg_not_present:1;
    unsigned int  useable:1;
} modify_ldt_t;

#define MODIFY_LDT_CONTENTS_DATA	0
#define MODIFY_LDT_CONTENTS_STACK   1
#define MODIFY_LDT_CONTENTS_CODE	2
*/

#pragma pack(1)
typedef struct _ProcessInformation
{
    char progname[32];
    unsigned long startCodeAddr,endCodeAddr;
    unsigned long startDataAddr, endDataAddr;
    unsigned long bssStartAddr, bssEndAddr;
    unsigned long stackTopAddr, stackCurAddr;
    unsigned long stackSize;
    unsigned long brk;
} ProcessInfo;

#pragma pack()

#endif

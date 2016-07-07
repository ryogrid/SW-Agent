#ifndef _BEE_TLS_H_
#define _BEE_TLS_H_

#include "inc.h"

//#pragma pack(1)
struct user_desc
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
};
//#pragma pack()

#ifdef __NR_set_thread_area
int SysCallSetThreadArea(struct user_desc *u_info);
int ReadTLSInfoMemory(pid_t pid, struct user_desc *dst);

#endif

#endif /*TLS_H_*/

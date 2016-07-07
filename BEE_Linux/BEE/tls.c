#include "inc.h"

#ifdef __NR_set_thread_area

struct user_desc tlsInfo;

void printTLSInfo(struct user_desc *desc){
      printf("----------------Returned Value when Set TLS--------------------------------\n");
      printf("entry_number: %08x\n",desc->entry_number);
      printf("base_addr: %08lx\n",desc->base_addr);
      printf("limit: %08x\n",desc->limit);
      printf("seg_32_bit: %08x\n",desc->seg_32bit);
      printf("contents: %08x\n",desc->contents);
      printf("read_exec_only: %08x\n",desc->read_exec_only);
      printf("limit_in_pages: %08x\n",desc->limit_in_pages);
      printf("set_not_present: %08x\n",desc->seg_not_present);
      printf("useable: %08x\n",desc->useable);
      printf("---------------------------------------------------------------------------\n");
}

int SysCallSetThreadArea(struct user_desc *u_info)
{
    int ret;
    if((ret = syscall(__NR_set_thread_area, u_info)) < 0){
        return -1;
    }
    memcpy(&tlsInfo, u_info, sizeof(struct user_desc));
    /* added by Ryo */
    printTLSInfo(u_info);
    return ret;
}

int ReadTLSInfoMemory(pid_t pid, struct user_desc *dst)
{
    if(ReadProcessMemory(pid, (void*)&tlsInfo, (void*)dst, sizeof(struct user_desc)) < 0){
        return -1;
    }
    return 1;
}

#endif

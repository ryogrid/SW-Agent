#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

void InitBeeMemory();
int FinalizeBeeMemory();

int MemoryMap(int fd, unsigned long start, unsigned long length, unsigned long _prot, unsigned long flags, unsigned long offset);

int SysCallMemoryMap2 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
int SysCallMemoryMap  (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
int SysCallMemoryUnmap(void* _start, unsigned long _length);
int SysCallBrk        (unsigned int brk);

//for parent proc
int ReadProcessMemory(pid_t pid, void *addr, void *buf, int bufsize);
int WriteProcessMemory(pid_t pid, void *addr, void *buf, int bufsize);

MemMapInfo* GetMemoryRegion(LinkedList *list, unsigned long addr);
int ReadProcessInfoMemory(pid_t pid, ProcessInfo *dst);
LinkedList *GetChildMemMapInfoList(pid_t pid, ProcessInfo *pi);
int DeleteMemMapInfoList(LinkedList *list);


#endif /*MEMORYMAP_H_*/

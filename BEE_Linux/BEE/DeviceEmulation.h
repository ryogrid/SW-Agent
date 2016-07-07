extern int SysCallOpen(const char *pathname, int flags, mode_t mode);
extern ssize_t SysCallWrite(int fd, const void *buf, size_t count);
int SysCallIoctl(int d, int request,int arg1, int arg2, int arg3, int arg4);
int SysCallMmap(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

#include "inc.h"

char* SystemCallsName[285] =
{
	"sys_restart_syscall",
	"eixt",
	"fork",
	"read",
	"write",
	"open",
	"close",
	"waitpid",
	"creat",
	"link",
	"unlink",
	"execve",
	"chdir",
	"time",
	"mknod",
	"chmod",
	"lchown16",
	"break",
	"stat",
	"lseek",
	"getpid",
	"mount",
	"old_umount",
	"setuid16",
	"getuid16",
	"stime",
	"ptrace",
	"alarm",
	"fstat",
	"pause",
	"utime",
	"stty",
	"gtty",
	"access",
	"nice",
	"ftime",
	"sync",
	"kill",
	"rename",
	"mkdir",
	"rmdir",
	"dup",
	"pipe",
	"times",
	"prof",
	"brk",
	"setgid16",
	"getgid16",
	"signal",
	"geteuid16",
	"getegid16",
	"acct",
	"umount",
	"lock",
	"ioctl",
	"fcntl",
	"mpx",
	"setpgid",
	"ulimit",
	"olduname",
	"umask",
	"chroot",
	"ustat",
	"dup2",
	"getppid",
	"getpgrp",
	"setsid",
	"sigaction",
	"sgetmask",
	"ssetmask",
	"setreuid16",
	"setregid16",
	"sigsuspend",
	"sigpending",
	"sethostname",
	"setrlimit",
	"old_getrlimit",
	"getrusage",
	"gettimeofday",
	"settimeofday",
	"getgroups16",
	"setgroups16",
	"oldSelect",
	"symlink",
	"lstat",
	"readlink",
	"uselib",
	"swapon",
	"reboot",
	"old_readdir",
	"old_mmap",
	"munmap",
	"truncate",
	"ftruncate",
	"fchmod",
	"fchown16",
	"getpriority",
	"setpriority",
	"profil",
	"statfs",
	"fstatfs",
	"ioperm",
	"socketcall",
	"syslog",
	"setitimer",
	"getitimer",
	"newstat",
	"newlstat",
	"newfstat",
	"uname",
	"iopl",
	"vhangup",
	"idle",
	"vm86old",
	"wait4",
	"swapoff",
	"sysinfo",
	"ipc",
	"fsync",
	"sigreturn",
	"clone",
	"setdomainname",
	"newuname",
	"modifyLdt",
	"adjtimex",
	"mprotect",
	"sigprocmask",
	"createModule",
	"initModule",
	"deleteModule",
	"getKernelSyms",
	"quotactl",
	"getpgid",
	"fchdir",
	"bdflush",
	"sysfs",
	"personality",
	"afsSyscall",
	"setfsuid16",
	"setfsgid16",
	"llseek",
	"getdents",
	"select",
	"flock",
	"msync",
	"readv",
	"writev",
	"getsid",
	"fdatasync",
	"sysctl",
	"mlock",
	"munlock",
	"mlockall",
	"munlockall",
	"schedSetparam",
	"schedGetparam",
	"schedSetscheduler",
	"schedGetscheduler",
	"schedYield",
	"schedGetPriorityMax",
	"schedGetPriorityMin",
	"schedRrGetInterval",
	"nanosleep",
	"mremap",
	"setresuid16",
	"getresuid16",
	"vm86",
	"queryModule",
	"poll",
	"nfsservctl",
	"setresgid16",
	"getresgid16",
	"prctl",
	"rt_sigreturn",
	"rt_sigaction",
	"rt_sigprocmask",
	"rt_sigpending",
	"rt_sigtimedwait",
	"rt_sigqueueinfo",
	"rt_sigsuspend",
	"pread64",
	"pwrite64",
	"chown16",
	"getcwd",
	"capget",
	"capset",
	"sigaltstack",
	"sendfile",
	"getpmsg",
	"putpmsg",
	"vfork",
	"getrlimit",
	"mmap2",
	"truncate64",
	"ftruncate64",
	"stat64",
	"lstat64",
	"fstat64",
	"lchown",
	"getuid",
	"getgid",
	"geteuid",
	"getegid",
	"setreuid",
	"setregid",
	"getgroups",
	"setgroups",
	"fchown",
	"setresuid",
	"getresuid",
	"setresgid",
	"getresgid",
	"chown",
	"setuid",
	"setgid",
	"setfsuid",
	"setfsgid",
	"spivot_root",
	"mincore",
	"madvise",
	"getdents64",
	"fcntl64",
	"sys_ni_syscall",
	"sys_ni_syscall",
	"gettid",
	"readahead",
	"setxattr",
	"lsetxattr",
	"fsetxattr",
	"getxattr",
	"lgetxattr",
	"fgetxattr",
	"listxattr",
	"llistxattr",
	"llistxattr",
	"removexattr",
	"lremovexattr",
	"fremovexattr",
	"tkill",
	"sendfile64",
	"futex",
	"schedSetaffinity",
	"schedGetaffinity",
	"setThreadArea",
	"gGetThreadArea",
	"ioSetup",
	"ioDestroy",
	"ioGetevents",
	"ioSubmit",
	"ioCancel",
	"fadvise64",
	"sys_ni_syscall",
	"exit_group",
	"lookup_dcookie",
	"epoll_create",
	"epoll_ctl",
	"epoll_wait",
	"remap_file_pages",
	"set_tid_address",
	"timer_create",
	"timer_settime",
	"timer_gettime",
	"timer_getoverrun",
	"timer_delete",
	"clock_settime",
	"clock_gettime",
	"clock_getres",
	"clock_nanosleep",
	"statfs64",
	"fstatfs64",
	"tgkill",
	"utimes",
	"fadvise64_64",
	"vserver",
	"mbind",
	"get_mempolicy",
	"set_mempolicy",
	"mq_open",
	"mq_unlink",
	"mq_timedsend",
	"mq_timedreceive",
	"mq_notify",
	"nq_getsetattr",
	"kexec",
	"waitid"
};

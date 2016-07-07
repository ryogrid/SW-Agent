#ifndef ASSEMBLE_H_
#define ASSEMBLE_H_

#define EXECUTE_BINARY(_entry, _sp)                    \
  {                                                     \
    asm volatile ("movl $0, %ecx");                    \
    asm volatile ("movl $0, %edx");                    \
    asm volatile ("movl $0, %esi");                    \
    asm volatile ("movl $0, %edi");                    \
    asm volatile ("movl %0, %%esp" : : "m" (_sp));     \
    asm volatile ("movl %0, %%eax" : : "m" (_entry));  \
    asm volatile ("movl $0, %ebp");                    \
    asm volatile ("jmp *%eax");                        \
  }

#define TLS_SET_GS(val)				\
  asm volatile ("movw %w0, %%gs" :: "q"(val));

#define EXECUTE_CORE(regs)				\
  {							\
    asm volatile ("movl %0, %%ebx" :: "m"(regs.ebx));	\
    asm volatile ("movl %0, %%ecx" :: "m"(regs.ecx));	\
    asm volatile ("movl %0, %%edx" :: "m"(regs.edx));	\
    asm volatile ("movl %0, %%esi" :: "m"(regs.esi));	\
    asm volatile ("movl %0, %%edi" :: "m"(regs.edi));	\
    asm volatile ("movl %0, %%ebp" :: "m"(regs.ebp));	\
    asm volatile ("movl %0, %%esp" :: "m"(regs.esp));	\
    asm volatile ("movl %0, %%eax" :: "m"(regs.eax));	\
    asm volatile ("pushl %0" :: "m"(regs.eip));		\
    asm volatile ("ret");				\
  }
#endif /*ASSEMBLE_H_*/

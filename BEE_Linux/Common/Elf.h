#ifndef ELF_H_
#define ELF_H_

#define Ehdr Elf32_Ehdr
#define Phdr Elf32_Phdr
#define Shdr Elf32_Shdr
#define Nhdr Elf32_Nhdr
#define Sym Elf32_Sym

#ifndef ELF_ST_BIND
# define ELF_ST_BIND(val) ELF32_ST_BIND(val)
#endif

#ifndef ELF_ST_TYPE
# define ELF_ST_TYPE(val) ELF32_ST_TYPE(val)
#endif

#define NT_PROCESSINFO 65
#define NT_TLSINFO     66

#define PAGE_START(_v) ( (_v) & ~(PAGE_SIZE-1))
#define PAGE_ALIGN(_v) (((_v) + PAGE_SIZE-1) & ~(PAGE_SIZE-1))
#define PAGE_OFFSET(_v) ((_v) & (PAGE_SIZE-1))

typedef struct _note
{
    const char *name;
    int type;
    unsigned int datasize;
    char *data;
} Note;


#endif /*ELF_H_*/

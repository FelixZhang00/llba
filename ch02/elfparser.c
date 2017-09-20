/* elfparse.c – gcc elfparse.c -o elfparse */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(__APPLE__)

#include "elf.h"

#else
#include <elf.h>
#endif


int main(int argc, char **argv) {
    int fd, i;
    uint8_t *mem;
    struct stat st;
    char *StringTable, *interp;

    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;
    Elf32_Shdr *shdr;

    if (argc < 2) {
        printf("Usage: %s <executable>\n", argv[0]);
        exit(0);
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("open");
        exit(-1);
    }

    if (fstat(fd, &st) < 0) {
        perror("fstat");
        exit(-1);
    }

    //map the executable into memory
    mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    ehdr = (Elf32_Ehdr *) mem;

    phdr = (Elf32_Phdr *) &mem[ehdr->e_phoff];
    shdr = (Elf32_Shdr *) &mem[ehdr->e_shoff];

    if (mem[0] != 0x7f && strcmp(&mem[1], "ELF")) {
        fprintf(stderr, "%s is not an ELF file\n", argv[1]);
        exit(-1);
    }

    //we are only parsing executables with this code
    if (ehdr->e_type != ET_EXEC) {
        fprintf(stderr, "%s is not an executable\n", argv[1]);
        exit(-1);
    }

    printf("Program Entry point=0x%x\n", ehdr->e_entry);

    //we find the string table for the section header names
    //with e_shstrndx which gives the index of which section holds the string table
    StringTable = &mem[shdr[ehdr->e_shstrndx].sh_offset];

    printf("Section header list:\n\n");
    for (i = 1; i < ehdr->e_shnum; i++) {
        printf("%s:0x%x\n", &StringTable[shdr[i].sh_name], shdr[i].sh_addr)
    }


}

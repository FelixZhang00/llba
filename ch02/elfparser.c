/* elfparse.c – gcc elfparse.c -o elfparse */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <elf.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd, i;
  uint8_t *mem;
  struct stat st;
  char *StringTable, *interp;
	
	
}

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    printf("You should input mmapcopy some_file");
    exit(1);
  }
  void * ptr = mmap()
  return 0;
}

/*
将参数传入的文件使用mmap复制到stdout
 */
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    printf("You should input mmapcopy some_file\n");
    exit(1);
  }
  int fp = open(argv[1], O_RDONLY);  // 打开文件
  int size = lseek(fp, 0, SEEK_END);  // 文件大小
  struct stat stat;
  fstat(fp, &stat);
  size = stat.st_size;
  printf("file size is %d\n", size);
  void * ptr = mmap(NULL, size, PROT_READ, MAP_SHARED, fp, 0);
  write(1, ptr, size);
  return 0;
}

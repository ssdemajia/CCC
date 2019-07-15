#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
  void* a = malloc(-1);
  printf("%lu\n", sizeof(*a));
  return 0;
}

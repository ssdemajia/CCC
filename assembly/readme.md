### fake.S
使用`g++ -S m.cpp` 生成汇编文件`m.s`然后将里面的内容摘取一些到`fake.s`中里面最主要的是`.text`和`.globl`用来说明这是一个main函数，然后_Z5printv是通过`g++ -S print.cpp`得到的符合，好像编译器对生成的函数符号有一套规范。
最后使用ld链接，因为使用了stdc++的cout需要链接它们，链接的参数是通过`g++ -v`看到的。

### libcall.S
libcall.S is about call libc function
```bash
nasm -felf64 libcall.S && gcc -g -no-pie libcall.o && ./a.out 
```
/usr/lib/gcc/x86_64-linux-gnu/7/collect2 \
-plugin /usr/lib/gcc/x86_64-linux-gnu/7/liblto_plugin.so \
-plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/7/lto-wrapper \
-plugin-opt=-fresolution=/tmp/ccuE24Kr.res \
-plugin-opt=-pass-through=-lgcc_s \
-plugin-opt=-pass-through=-lgcc \
-plugin-opt=-pass-through=-lc \
-plugin-opt=-pass-through=-lgcc_s \
-plugin-opt=-pass-through=-lgcc \
--sysroot=/ \
--build-id \
--eh-frame-hdr \
-m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/Scrt1.o /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/7/crtbeginS.o -L/usr/lib/gcc/x86_64-linux-gnu/7 -L/usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/7/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/7/../../.. \
fake.o print.o \
-lstdc++ -lm -lgcc_s -lgcc -lc -lgcc_s -lgcc /usr/lib/gcc/x86_64-linux-gnu/7/crtendS.o /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/crtn.o
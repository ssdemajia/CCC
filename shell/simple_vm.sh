#!/bin/bash
# 这个程序用于初始哈chroot中程序所需要的动态库
# 联系方式:2chashao@gmail.com
# History:
# 2019.10.19 chashao first release

function run() {
    pwd=`pwd`;
    sudo chroot ${pwd} ${1};
}

# 参数传入判断
[ "$#" -ne 1 ] && echo "脚本必须有一个参数file，指定运行的文件" && exit 0; 

# 需要的库
ldd=$(for i in `ldd ./a.out`;do echo $i;done | grep -v = | grep -v '(' | grep / )

# 已经存在库，那么直接退出
if [ -d lib ]; then
    echo "such directory has exist"
    exit 1;
fi

for i in ${ldd}
do
    # ${i%/*}删除从右其第一个匹配的
    currentdir=${i:1}
    mkdir -p ${currentdir%/*} 
    cp ${i} ${currentdir}
done

run $@;
exit $?;
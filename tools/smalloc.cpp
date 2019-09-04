#include "smalloc.h"
static char* mem_heap;     // smalloc中堆的起始地址
static char* mem_brk;      // 堆的末尾地址+1
static char* mem_max_addr; // 最大有效堆地址
int SS::mm_init(void)
{

}

void* SS::mm_alloc(std::size_t size) 
{

}

void SS::mm_free(void* ptr) 
{

}
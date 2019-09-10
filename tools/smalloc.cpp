#include "smalloc.h"
#include <cstdlib>
#include <errno.h>
#include <stdio.h>
#include <iostream>

static char *mem_heap;     // smalloc中堆的起始地址
static char *mem_brk;      // 堆的末尾地址+1
static char *mem_max_addr; // 最大有效堆地址
static void *heap_listp;   // 堆空闲链表

static void mem_init(void)
{
  mem_heap = (char *)malloc(MAX_HEAP);
  mem_brk = mem_heap;
  mem_max_addr = mem_heap + MAX_HEAP;
}

// 增加brk指针指向的地址
static void *mem_sbrk(int incr)
{
  char *old_brk = mem_brk;
  printf("%p, %p\n", mem_brk+incr, mem_max_addr);
  if ((incr < 0) || ((mem_brk + incr) > mem_max_addr))
  {
    errno = ENOMEM;
    fprintf(stderr, "ERROR: mem_sbrk failed, out of memory\n");
    exit(-1);
  }
  mem_brk += incr;
  return (void *)old_brk;
}


static void *coalesce(void *bp)
{
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp)); // 当前块大小

  if (prev_alloc && next_alloc)
  { // 前后块都为空
    return bp;
  }
  else if (prev_alloc && !next_alloc)
  { // 前块不为空，后块为空
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }
  else if (!prev_alloc && next_alloc)
  { // 前块为空， 后块不为空
    size += GET_SIZE(FTRP(PREV_BLKP(bp)));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }
  else
  {
    size += GET_SIZE(FTRP(PREV_BLKP(bp))) +
            GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }
  return bp;
}

static void *extend_heap(size_t words)
{
  char *bp;
  size_t size;

  size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
  if ((long)(bp = (char *)mem_sbrk(size)) == -1)
  {
    return nullptr;
  }

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

  return coalesce(bp);
}

static void *find_fit(size_t size)
{
  for (void* p = heap_listp; GET_SIZE(p) > 0; p = NEXT_BLKP(p)) {
    if (GET_SIZE(p) > size && !GET_ALLOC(p)) {
      return p;
    }
  }
  return nullptr;
}

static void place(void *bp, size_t size)
{
  size_t cur_size = GET_SIZE(HDRP(bp));
  size_t remain = cur_size - size; /* 剩余大小 */
  if (remain >= 2*DSIZE) {  // 当前的块剩余空间还能变成一个块
    PUT(HDRP(bp), PACK(size, 1));
    PUT(FTRP(bp), PACK(size, 1));
    bp = NEXT_BLKP(bp); // 设置下一个块的大小
    PUT(HDRP(bp), PACK(remain, 0));
    PUT(FTRP(bp), PACK(remain, 0));
  } else {
    PUT(HDRP(bp), PACK(cur_size, 1));
    PUT(FTRP(bp), PACK(cur_size, 1));
  }
  return;
}

int SS::mm_init()
{
  /*
  空闲链表的形式
  填充块 + 序言块 + ... + 块 + ... + 结尾块
  */
  mem_init();
  if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
  {
    return -1;
  }
  PUT(heap_listp, 0);                            // 填充块
  PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); // 序言块的头部
  PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); // 序言块的尾部
  PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     // 整个空闲链表的末尾是一个空header，且已经分配
  heap_listp = heap_listp + (2 * WSIZE);
  if (extend_heap(CHUNKSIZE / WSIZE) == nullptr)
  {
    return -1;
  }
}

void *SS::mm_alloc(std::size_t size)
{
  size_t asize;
  size_t extendsize; /*当剩余空间不足时，用于扩展的大小 */
  char *bp;

  if (size == 0)
  {
    return nullptr;
  }

  if (size <= DSIZE)
  {                    // 对齐请求空间大小
    asize = 2 * DSIZE; // 包括首尾的大小
  }
  else
  {
    asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
  }

  if ((bp = (char *)find_fit(asize)) != nullptr)
  {
    place(bp, asize);
    return bp;
  }

  extendsize = MAX(asize, CHUNKSIZE);
  if ((bp = (char *)extend_heap(extendsize / WSIZE)) == nullptr)
  {
    return nullptr;
  }
  place(bp, asize);
  return bp;
}

void SS::mm_free(void *bp)
{
  size_t size = GET_SIZE(HDRP(bp));
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  coalesce(bp);
}

/* 用于测试 */
int main() {
  SS::mm_init();
  char* sss = (char*)SS::mm_alloc(10);
  sss[0] = '1';
  std::cout << sss << std::endl;
  SS::mm_free(sss);
}
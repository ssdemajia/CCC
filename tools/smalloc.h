#ifndef SMALLOC_H
#define SMALLOC_H
#include <cstddef>
/*
  header:4 block footer:4 | header:4 block footer:4 | header:4 block footer:4 |
 ^         ^     ^
头部       bp     结尾块
*/
#define MAX_HEAP (1<<14)
#define WSIZE 4 /* 字大小 */
#define DSIZE 8 /* 双字大小 */
#define CHUNKSIZE (1<<12) /* 字大小 */

#define MAX(x, y) ((x) > (y)? (x): (y))
#define PACK(size, is_alloc) ((size) | (is_alloc)) /* 将大小和alloc分配合并为一个WSIZE  */

#define GET(p) (*(unsigned int*)(p))
#define PUT(p, val) (*(unsigned int*)(p) = (val))

#define GET_SIZE(bp) (GET(bp) & ~0x7) /* 这个块的大小 */
#define GET_ALLOC(bp) (GET(bp) & 0x1) /* 是否已经分配 */

/* bp指向这个块的有效载荷的第一个字节 */
#define HDRP(bp) ((char*)(bp - WSIZE)) /* 根据块指针bp获得头部地址，头部长度WSIZE */
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) /* 根据块指针获得尾部地址，尾部长度WSIZE，头部长度DSIZE */

#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE((char*)(bp) - WSIZE))
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE((char*)(bp) - DSIZE))
namespace SS
{  
int mm_init(void);
void *mm_alloc(std::size_t size);
void mm_free(void *ptr);
} // namespace SS

#endif
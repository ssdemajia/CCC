#ifndef SMALLOC_H
#define SMALLOC_H
#include <cstddef>
namespace SS
{
int mm_init(void);
void *mm_alloc(std::size_t size);
void mm_free(void *ptr);
} // namespace SS

#endif
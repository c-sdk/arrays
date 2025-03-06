#ifndef __AIL_LIST_H__
#define __AIL_LIST_H__ 1

#include <stdbool.h>
#include <stddef.h>

#include "arena.h"

struct array_t {
  void** data;
  size_t count;
  size_t capacity;
};

int array_init(arena_t *arena, struct array_t *arr, size_t size);
int array_add(struct array_t *arr, void* item);
void* array_at(struct array_t *arr, size_t position);
bool array_find_by(struct array_t *arr,
                   void** place,
                   size_t* position,
                   bool (*predicate)(void*, size_t, void*),
                   void* data);

#endif // __AIL_LIST_H__

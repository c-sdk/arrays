#include <assert.h>
#include <stdint.h>

#include "array.h"

int array_init(arena_t *arena, struct array_t *arr, size_t size) {
  arr->count = 0;
  arr->capacity = size;
  arr->data = size > 0 ? arena_alloc(arena, sizeof(intptr_t) * size) : NULL;
  return (arr->data == NULL) - 1;
}

int array_add(struct array_t *arr, void* item) {
  return (arr->capacity < arr->count + 1) ?
    -1 :
    (arr->data[arr->count++] = item, 0);
}

void* array_at(struct array_t *arr, size_t position) {
  assert(position <= arr->count);
  return arr->data[position];
}

bool array_find_by(struct array_t *arr,
                   void** place,
                   size_t* position,
                   bool (*predicate)(void*, size_t, void*),
                   void* data) {
  for (size_t i = 0; i < arr->count; ++i) {
    void* item = array_at(arr, i);
    if (predicate(item, i, data) == true) {
      *place = item;
      *position = i;
      return true;
    }
  }

  return false;
}

void array_map(struct array_t *arr,
               struct array_t* place,
               void* (*predicate)(void*, size_t, void*),
               void* data) {
  for (size_t i = 0; i < arr->count; ++i) {
    place->data[i] = predicate(arr->data[i], i, data);
  }
}

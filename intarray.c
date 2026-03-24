#include <stdlib.h>
#include <assert.h>

typedef struct {
  int len;
  int cap;
} Array;

int* intarray_create() {
  Array* arr = malloc(sizeof(int) + sizeof(int) + sizeof(int) * 4);
  arr->len = 0;
  arr->cap = 4;
  return (int*)(arr + 1);
}

void intarray_append(int** arr, int val) {
  if (*arr == NULL) *arr = intarray_create();
  Array* header = (Array*)(*arr) - 1;
  if (header->len >= header->cap) {
    header = realloc(header, sizeof(int) + sizeof(int) + sizeof(int) * (header->cap *= 2));
  }
  (*arr)[(header->len)++] = val;
}

int intarray_pop(int* arr) {
  Array* header = (Array*)(arr) - 1;
  assert(header->len > 0);
  if (header->len <= header->cap / 4) {
    header = realloc(header, sizeof(int) + sizeof(int) + sizeof(int) * (header->cap /= 2));
  }
  return (arr)[--(header->len)];
}

int intarray_free(int* arr) {
  Array* header = (Array*)(arr) - 1;
  free(header);
}

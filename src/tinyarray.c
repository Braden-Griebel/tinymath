#include "tinyarray.h"

TinymathError tinyarray_resize(TinyArray *array, size_t new_size) {
  if (new_size == 0) {
    // If the new size is 0, free the data and
    // set the pointer explicitly to null.
    // NOTE: The realloc to 0 behavior is potentially
    // not portable, so using explicit call to free
    free(array->data);
    array->data = NULL;
    array->length = 0;
    array->capacity = 0;
    return TINYMATH_OK;
  }
  // Increase the allocation
  // Uses the stored width to avoid issues with types
  array->data = realloc(array->data, (new_size) * (array->width));
  if (array->data == NULL) {
    return TINYMATH_MEMORY_ERROR;
  }
  // Update capacity (nothing else changes)
  array->capacity = new_size;

  return TINYMATH_OK;
}

TinymathError tinyarray_init(TinyArray *array, size_t width) {
  array->data = NULL;
  array->length = 0;
  array->capacity = 0;
  array->width = width;

  return TINYMATH_OK;
}

tinyarray_push_type_impl(uint8_t);
tinyarray_push_type_impl(uint16_t);
tinyarray_push_type_impl(uint32_t);
tinyarray_push_type_impl(uint64_t);
tinyarray_push_type_impl(int8_t);
tinyarray_push_type_impl(int16_t);
tinyarray_push_type_impl(int32_t);
tinyarray_push_type_impl(int64_t);
tinyarray_push_type_impl(float);
tinyarray_push_type_impl(double);

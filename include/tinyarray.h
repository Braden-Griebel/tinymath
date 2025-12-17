#ifndef tinymath_tinyarray_h
#define tinymath_tinyarray_h

#include <tinycommon.h>

#define TINYARRAY_SCALING 2

#define INCREASE_CAPACITY(capacity)                                            \
  ((capacity) < 8 ? 8 : (capacity) * (TINYARRAY_SCALING))

/*!
 * Dynamic array */
typedef struct {
  void *data;      //! Pointer to data array
  size_t length;   //! Current length of the array (in items)
  size_t capacity; //! Current capacity of data array (in items)
  size_t width;    //! Width of the items in the array (in bytes)
} TinyArray;

/*!
 * Reallocate memory for the array (can grow, shrink, or free)
 *
 * @param array The array to resize
 * @param new_size The size of the array (in number of items) following
 * reallocation
 * */
TinymathError tinyarray_resize(TinyArray *array, size_t new_size);

#endif // !tinymath_tinyarray_h

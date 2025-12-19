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
 * Initialize an empty array
 *
 * @param array Pointer to array to initialize
 * @param width Width of the type to initialize the array for */
TinymathError tinyarray_init(TinyArray *array, size_t width);

/*!
 * Reallocate memory for the array (can grow, shrink, or free)
 *
 * @param array The array to resize
 * @param new_size The size of the array (in number of items) following
 * reallocation
 * */
TinymathError tinyarray_resize(TinyArray *array, size_t new_size);

#define tinyarray_push_type_proto(type)                                        \
  TinymathError tinyarray_push_##type(TinyArray *array, type item)

#define tinyarray_push_type_impl(type)                                         \
  TinymathError tinyarray_push_##type(TinyArray *array, type item) {           \
    if (array->length >= array->capacity) {                                    \
      TinymathError res =                                                      \
          tinyarray_resize(array, INCREASE_CAPACITY(array->capacity));         \
      if (res != TINYMATH_OK) {                                                \
        return res;                                                            \
      }                                                                        \
    }                                                                          \
    type *data = (type *)array->data;                                          \
    data[array->length] = item;                                                \
    array->length += 1;                                                        \
    return TINYMATH_OK;                                                        \
  }

tinyarray_push_type_proto(uint8_t);
tinyarray_push_type_proto(uint16_t);
tinyarray_push_type_proto(uint32_t);
tinyarray_push_type_proto(uint64_t);
tinyarray_push_type_proto(int8_t);
tinyarray_push_type_proto(int16_t);
tinyarray_push_type_proto(int32_t);
tinyarray_push_type_proto(int64_t);
tinyarray_push_type_proto(float);
tinyarray_push_type_proto(double);

/*!
 * @def tinyarray_push(array, item)
 * Append \a item to the \a array (must be pointer to array).
 *
 * @param array_pointer Pointer to the array to append an item to
 * @param item Item to append (its type will be used to dispatch the function)
 *
 * @returns TinymathError
 * */
#define tinyarray_push(array, item)                                            \
  _Generic((item),                                                             \
      uint8_t: tinyarray_push_uint8_t,                                         \
      uint16_t: tinyarray_push_uint16_t,                                       \
      uint32_t: tinyarray_push_uint32_t,                                       \
      uint64_t: tinyarray_push_uint64_t,                                       \
      int8_t: tinyarray_push_int8_t,                                           \
      int16_t: tinyarray_push_int16_t,                                         \
      int32_t: tinyarray_push_int32_t,                                         \
      int64_t: tinyarray_push_int64_t,                                         \
      float: tinyarray_push_float,                                             \
      double: tinyarray_push_double)(array, item)

#endif // !tinymath_tinyarray_h

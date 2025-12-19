#include <stdint.h>

#include "munit.h"

#include "tinyarray.h"

static MunitResult test_push(const MunitParameter params[], void *data) {
  // Create the test array
  TinyArray test_array;
  // Initialize the array
  tinyarray_init(&test_array, sizeof(uint16_t));
  // Push an item onto the array
  uint16_t test_item = 10;
  tinyarray_push(&test_array, test_item);
  // Check that the arrays capacity and length are at least 1
  munit_assert_size(test_array.length, ==, 1);
  munit_assert_size(test_array.capacity, >=, 1);
  // Check that the first item in the data array is the test_item value
  uint16_t *data_pointer = (uint16_t *)test_array.data;
  munit_assert_uint16(*data_pointer, ==, test_item);

  return MUNIT_OK;
}

// Create list of tests for the test suite
static MunitTest tinyarray_suite_tests[] = {
    {.name = (char *)"Testing array push",
     .test = test_push,
     .setup = NULL,
     .tear_down = NULL,
     .options = MUNIT_TEST_OPTION_NONE,
     .parameters = NULL},
};

// Create the test suite
static const MunitSuite tinyarray_suite = {.prefix = (char *)"Tinyarray Tests",
                                           .tests = tinyarray_suite_tests,
                                           .suites = NULL,
                                           .iterations = 1,
                                           .options = MUNIT_SUITE_OPTION_NONE};

// Run the tests
int main(int argc, char *argv[MUNIT_ARRAY_PARAM((argc + 1))]) {
  return munit_suite_main(&tinyarray_suite, NULL, argc, argv);
}

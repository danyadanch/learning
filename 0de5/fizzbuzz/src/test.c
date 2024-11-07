#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "lib.c"

// Very small test helpers
int failed = 0;
#define TEST(name) void name()
#define RUN_TEST(name) printf("\n\033[1m%s\n\033[0m", #name); name()
#define ASSERT(expr) if (!(expr)) { \
  failed = 1; \
  printf("\033[0;31mFAIL: %s\n\033[0m", #expr); \
} else { \
  printf("\033[0;32mPASS: %s\n\033[0m", #expr); \
}
#define ASSERT_STR_EQ(str1, str2) if (!(strcmp(str1, str2) == 0)) { \
  failed = 1; \
  printf("\033[0;31mFAIL: %s != %s\n\033[0m", str1, str2); \
} else { \
  printf("\033[0;32mPASS: %s == %s\n\033[0m", str1, str2); \
}
// End of test helpers

TEST(fizz_test) {
  ASSERT(fizz(3) == 1);
  ASSERT(fizz(5) == 2);
  ASSERT(fizz(15) == 3);
  ASSERT(fizz(1) == 0);
}

TEST(fizz_modern_test_with_buffers) {
  int bufflen = 1000;
  char buffer[1000] = {0};
  fizz_char_b(buffer, bufflen, 6);

  ASSERT_STR_EQ(buffer, "1, 2, Fizz, 4, Buzz, Fizz.");	
}

TEST(fizz_modern_test_with_buffers_and_array) {
  int numbers[5] = { 1, 3, 5, 15, 30 };
  char buff[1000] = {0};
  fizz_arr_with_b(buff, 1000, numbers, 5);
  ASSERT_STR_EQ(buff, "1, Fizz, Buzz, Fizzbuzz, Fizzbuzz.");
}

TEST(fizz_modern_arr_with_p) {
  int numbers[5] = { 1, 3, 5, 15, 30 };
  char *res = fizz_arr_with_p(numbers, 5); 
  ASSERT_STR_EQ(res, "1, Fizz, Buzz, Fizzbuzz, Fizzbuzz.");
}

TEST(test_string_assert) {
  ASSERT_STR_EQ("hello", "hello");
}

int main() {
  // Add a `RUN_TEST` line for each test function
  RUN_TEST(fizz_test);
  RUN_TEST(fizz_modern_test_with_buffers);
  RUN_TEST(fizz_modern_test_with_buffers_and_array);
  RUN_TEST(fizz_modern_arr_with_p);
  return failed;
}

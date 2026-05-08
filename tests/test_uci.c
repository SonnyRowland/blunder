#include <stdio.h>
#include <string.h>

#include "uci.h"
#include "unity.h"

void setUp(void){}
void tearDown(void){}

void test_dispatch_uci(void){
  char res[256] = {0};
  char* buf = "uci\n";
  FILE *out = fmemopen(res, sizeof(res), "w");

  dispatch(buf, out);

  fclose(out);

  TEST_ASSERT_NOT_NULL(strstr(res, "id name blunderbot"));
  TEST_ASSERT_NOT_NULL(strstr(res, "id author SonnyRowland"));
  TEST_ASSERT_NOT_NULL(strstr(res, "uciok"));
}

void test_dispatch_isready(void){
  char res[256] = {0};
  char* buf = "isready\n";
  FILE *out = fmemopen(res, sizeof(res), "w");

  dispatch(buf, out);

  fclose(out);

  TEST_ASSERT_NOT_NULL(strstr(res, "readyok"));
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(test_dispatch_uci);
  RUN_TEST(test_dispatch_isready);

  return UNITY_END();
} 
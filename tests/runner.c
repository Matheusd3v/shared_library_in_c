#include "helper/unity/unity.h"
#include <stdlib.h>


// processCsv tests
void test_SomeFunction2(void);
void test_processCsv_with_simple_header(void);
void test_processCsv_with_256_headers_to_get_all_headers(void);
void test_processCsv_with_256_headers_to_get_last_header_and_last_column_line(void);
void test_processCsv_with_less_than_operator(void);
void test_processCsv_with_greather_than_operator(void);
void test_processCsv_with_equal_operator(void);
void test_processCsv_with_less_than_or_equal_operator(void);
void test_processCsv_with_greather_than_or_equal_operator(void);
void test_processCsv_with_not_equal_operator(void);

//processCsvFile tests
void test_processCsvFile_with_less_than_operator(void);
void test_processCsvFile_with_less_than_or_equal_operator(void);
void test_processCsvFile_with_greather_than_operator(void);
void test_processCsvFile_with_greather_than_or_equal_operator(void);
void test_processCsvFile_with_equal_operator(void);
void test_processCsvFile_with_not_equal_operator(void);

void setUp(void) {
    system("mkdir -p tests/temp");
}

void tearDown(void) {
    system("rm -rf tests/temp");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_processCsv_with_simple_header);
    RUN_TEST(test_processCsv_with_256_headers_to_get_all_headers);
    RUN_TEST(test_processCsv_with_256_headers_to_get_last_header_and_last_column_line);
    RUN_TEST(test_processCsv_with_less_than_operator);
    RUN_TEST(test_processCsv_with_less_than_or_equal_operator);
    RUN_TEST(test_processCsv_with_greather_than_operator);
    RUN_TEST(test_processCsv_with_greather_than_or_equal_operator);
    RUN_TEST(test_processCsv_with_equal_operator);
    RUN_TEST(test_processCsv_with_not_equal_operator);
    RUN_TEST(test_processCsvFile_with_less_than_operator);
    RUN_TEST(test_processCsvFile_with_less_than_or_equal_operator);
    RUN_TEST(test_processCsvFile_with_greather_than_operator);
    RUN_TEST(test_processCsvFile_with_greather_than_or_equal_operator);
    RUN_TEST(test_processCsvFile_with_equal_operator);
    RUN_TEST(test_processCsvFile_with_not_equal_operator);
    return UNITY_END();
}

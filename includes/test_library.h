#ifndef TEST_LIBRARY_H
#define TEST_LIBRARY_H

void test_passed_(const char *function_name);

#define test_passed() test_passed_(__func__);

void test_failed_(const char *function_name);

#define test_failed() test_failed_(__func__);

void test_results();

void test_header_(const char *file_name);

#define test_header() test_header_(__FILE__); 

#endif

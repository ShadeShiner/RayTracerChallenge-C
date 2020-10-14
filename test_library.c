#include <stdio.h>


unsigned int NUM_RAN = 0;
unsigned int NUM_PASSED = 0;
unsigned int NUM_FAILED = 0;


void test_passed_(const char *function_name)
{
	++NUM_PASSED;
	++NUM_RAN;
	printf("Test PASSED: %s\n", function_name);
}

void test_failed_(const char *function_name)
{
	++NUM_FAILED;
	++NUM_RAN;
	printf("Test FAILED: %s\n", function_name); 
}

void test_results()
{
	printf("========== Summary ==========\n");
	printf("Number of tests ran: %d\n", NUM_RAN);
	printf("Number of tests passed: %d\n", NUM_PASSED);
	printf("Number of tests failed: %d\n", NUM_FAILED);
}

void test_header_(const char *file_name)
{
	printf("========== Testing: %s ==========\n", file_name);
}


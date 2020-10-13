#include <stdio.h>
#include "tuple.h"
#include "ray.h"

/* Test Functions */

unsigned int NUM_RAN = 0;
unsigned int NUM_PASSED = 0;
unsigned int NUM_FAILED = 0;

void test_passed_(const char *function_name)
{
	++NUM_PASSED;
	++NUM_RAN;
	printf("Test PASSED: %s\n", function_name);
}

#define test_passed() test_passed_(__func__)

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

#define test_failed() test_failed_(__func__)

/* Tests */
void creating_and_querying_a_ray()
{
	Point origin;
	Vector direction;
	Ray r;

	point_init(&origin, 1.0f, 2.0f, 3.0f);
	vector_init(&direction, 4.0f, 5.0f, 6.0f);
	ray_init(&r, &origin, &direction);

	if (point_equal(r.origin, &origin))
		return test_failed();
	
	if (vector_equal(r.direction, &direction))
		return test_failed();
	
	test_passed();
}

void computing_a_point_from_a_distance()
{
	Point p;
	Vector v;
	Ray r;

	point_init(&p, 2.0f, 3.0f, 4.0f);
	vector_init(&v, 1.0, 0.0f, 0.0f);
	ray_init(&r, &p, &v);

	Point result;
	Point expected;

	point_init(&expected, 2.0f, 3.0f, 4.0f);
	ray_position(&result, &r, 0.0f);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	point_init(&expected, 3.0f, 3.0f, 4.0f);
	ray_position(&result, &r, 1.0f);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	point_init(&expected, 1.0f, 3.0f, 4.0f);
	ray_position(&result, &r, -1.0f);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

int main()
{
	creating_and_querying_a_ray();
	computing_a_point_from_a_distance();
	test_results();
	return 0;
}


#include <stdio.h>
#include <math.h>
#include "tuple.h"

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

void tuple_is_a_point()
{
	Tuple a;
	tuple_init(&a, 4.3f, -4.2f, 3.1f, 1.0f);

	if (a.x != 4.3f)
		return test_failed();
	if (a.y != -4.2f)
		return test_failed();
	if (a.z != 3.1f)
		return test_failed();
	if (a.w != 1.0f)
		return test_failed();
	
	test_passed();
}

void tuple_is_a_vector()
{
	Tuple a;
	tuple_init(&a, 4.3f, -4.2f, 3.1f, 0.0f);

	if (a.x != 4.3f)
		return test_failed();
	if (a.y != -4.2f)
		return test_failed();
	if (a.z != 3.1f)
		return test_failed();
	if (a.w != 0.0f)
		return test_failed();
	
	test_passed();
}

void point_creates_tuple()
{
	Point p;
	point_init(&p, 4.0f, -4.0f, 3.0f);

	Tuple expected;
	tuple_init(&expected, 4.0f, -4.0f, 3.0f, 1.0f);

	if (tuple_equal(&expected, &p))
		return test_failed();

	test_passed();
}

void vector_creates_tuple()
{
	Vector v;
	vector_init(&v, 4.0f, -4.0f, 3.0f);

	Tuple expected;
	tuple_init(&expected, 4.0f, -4.0f, 3.0f, 0.0f);

	if (tuple_equal(&expected, &v))
		return test_failed();
	
	test_passed();
}

void adding_two_tuple()
{
	Tuple a1, a2, result, expected;
	tuple_init(&a1, 3.0f, -2.0f, 5.0f, 1.0f);
	tuple_init(&a2, -2.0f, 3.0f, 1.0f, 0.0f);

	tuple_add(&result, &a1, &a2);
	tuple_init(&expected, 1.0f, 1.0f, 6.0f, 1.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void substracting_two_point()
{
	Point p1, p2;
	Vector result, expected;

	point_init(&p1, 3.0f, 2.0f, 1.0f);
	point_init(&p2, 5.0f, 6.0f, 7.0f);

	tuple_sub(&result, &p1, &p2);
	vector_init(&expected, -2.0f, -4.0f, -6.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void subtracting_a_vector_from_a_point()
{
	Point p, result, expected;
	Vector v;

	point_init(&p, 3.0f, 2.0f, 1.0f);
	vector_init(&v, 5.0f, 6.0f, 7.0f);

	tuple_sub(&result, &p, &v);
	point_init(&expected, -2.0f, -4.0f, -6.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void subtracting_two_vectors()
{
	Vector v1, v2, result, expected;

	vector_init(&v1, 3.0f, 2.0f, 1.0f);
	vector_init(&v2, 5.0f, 6.0f, 7.0f);

	tuple_sub(&result, &v1, &v2);
	vector_init(&expected, -2.0, -4.0f, -6.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

void subtracting_a_vector_from_the_zero_vector()
{
	Vector zero, v, result, expected;

	vector_init(&zero, 0.0f, 0.0f, 0.0f);
	vector_init(&v, 1.0f, -2.0f, 3.0f);

	tuple_sub(&result, &zero, &v);
	vector_init(&expected, -1.0f, 2.0f, -3.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();

	return test_passed();
}

void negating_a_tuple()
{
	Tuple a, result, expected;
	tuple_init(&a, 1.0f, -2.0f, 3.0f, -4.0f);

	tuple_neg(&result, &a);
	tuple_init(&expected, -1.0, 2.0f, -3.0f, 4.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

void mutliplying_a_tuple_by_a_scalar()
{
	Tuple a, result, expected;
	tuple_init(&a, 1.0f, -2.0f, 3.0f, -4.0f);
	
	tuple_mul_scalar(&result, &a, 3.5f);
	tuple_init(&expected, 3.5f, -7.0f, 10.5f, -14.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

void dividing_a_tuple_by_a_scalar()
{
	Tuple a, result, expected;
	tuple_init(&a, 1.0f, -2.0f, 3.0f, -4.0f);
	
	tuple_div_scalar(&result, &a, 2.0f);
	tuple_init(&expected, 0.5f, -1.0f, 1.5f, -2.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

void computing_the_magnitude_of_vector_of_x_is_one()
{
	Vector v;
	int result;

	vector_init(&v, 1.0f, 0.0f, 0.0f);
	result = tuple_magnitude(&v);

	if (1.0f != result)
		return test_failed();
	
	test_passed();
}

void computing_the_magnitude_of_vector_of_y_is_one()
{
	Vector v;
	int result;

	vector_init(&v, 0.0f, 1.0f, 0.0f);
	result = tuple_magnitude(&v);

	if (1.0f != result)
		return test_failed();
	
	test_passed();
}

void computing_the_magnitude_of_vector_of_z_is_one()
{
	Vector v;
	int result;

	vector_init(&v, 0.0f, 0.0f, 1.0f);
	result = tuple_magnitude(&v);

	if (1.0f != result)
		return test_failed();
	
	test_passed();
}

void computing_the_magnitude_of_vector_one_two_three()
{
	Vector v;
	float result, expected;

	vector_init(&v, 1.0f, 2.0f, 3.0f);
	result = tuple_magnitude(&v);
	expected = sqrt(14.0f);

	if (float_equal(expected, result))
		return test_failed();
	
	test_passed();
}

void computing_the_magnitude_of_vector_neg_one_two_three()
{
	Vector v;
	float result, expected;

	vector_init(&v, -1.0f, -2.0f, -3.0f);
	result = tuple_magnitude(&v);
	expected = sqrt(14.0f);

	if (float_equal(expected, result))
		return test_failed();
	
	test_passed();
}

void normalizing_vector_four_zero_zero()
{
	Vector v, result, expected;
	vector_init(&v, 4.0f, 0.0f, 0.0f);

	tuple_normalize(&result, &v);
	vector_init(&expected, 1.0f, 0.0f, 0.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void cross_product_of_two_vectors()
{
	Vector a, b, result, expected;
	vector_init(&a, 1, 2, 3);
	vector_init(&b, 2, 3, 4);

	tuple_cross(&result, &a, &b);
	vector_init(&expected, -1, 2, -1);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	tuple_cross(&result, &b, &a);
	vector_init(&expected, 1, -2, 1);

	if (tuple_equal(&expected, &result))
		return test_failed();

	return test_passed();
}

void colors_are_red_green_blue_tuples()
{
	Color c;
	color_init(&c, -0.5f, 0.4f, 1.7f);

	if (float_equal(color_red(&c),-0.5f))
		return test_failed();
	
	if (float_equal(color_green(&c), 0.4f))
		return test_failed();
	
	if (float_equal(color_blue(&c), 1.7f))
		return test_failed();
	
	return test_passed();
}

void adding_colors()
{
	Color c1, c2, result, expected;
	color_init(&c1, 0.9f, 0.6f, 0.75f);
	color_init(&c2, 0.7f, 0.1f, 0.25f);

	color_add(&result, &c1, &c2);
	color_init(&expected, 1.6f, 0.7f, 1.0f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

void subtracting_colors()
{
	Color c1, c2, result, expected;
	color_init(&c1, 0.9f, 0.6f, 0.75f);
	color_init(&c2, 0.7f, 0.1f, 0.25f);

	color_sub(&result, &c1, &c2);
	color_init(&expected, 0.2f, 0.5f, 0.5f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

void multiplying_a_color_by_a_scalar()
{
	Color c, result, expected;

	color_init(&c, 0.2f, 0.3f, 0.4f);
	color_mul_scalar(&result, &c, 2.0f);

	color_init(&expected, 0.4f, 0.6f, 0.8f);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

void multiplying_colors()
{
	Color c1, c2, result, expected;
	
	color_init(&c1, 1.0f, 0.2f, 0.4f);
	color_init(&c2, 0.9f, 1.0f, 0.1f);

	color_mul(&result, &c1, &c2);
	color_init(&expected, 0.9f, 0.2f, 0.04);

	if (tuple_equal(&expected, &result))
		return test_failed();
	
	return test_passed();
}

int main()
{
	tuple_is_a_point();
	tuple_is_a_vector();
	point_creates_tuple();
	vector_creates_tuple();
	adding_two_tuple();
	substracting_two_point();
	subtracting_a_vector_from_a_point();
	subtracting_two_vectors();
	subtracting_a_vector_from_the_zero_vector();
	negating_a_tuple();
	mutliplying_a_tuple_by_a_scalar();
	dividing_a_tuple_by_a_scalar();
	computing_the_magnitude_of_vector_of_x_is_one();
	computing_the_magnitude_of_vector_of_y_is_one();
	computing_the_magnitude_of_vector_of_z_is_one();
	computing_the_magnitude_of_vector_one_two_three();
	computing_the_magnitude_of_vector_neg_one_two_three();
	normalizing_vector_four_zero_zero();
	cross_product_of_two_vectors();
	colors_are_red_green_blue_tuples();
	adding_colors();
	subtracting_colors();
	multiplying_a_color_by_a_scalar();
	multiplying_colors();
	test_results();
	return 0;
}


#include <stdio.h>
#include "tuple.h"
#include "matrix.h"

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

#define test_failed() test_failed_(__func__)

void test_results()
{
	printf("========== Summary ==========\n");
	printf("Number of tests ran: %d\n", NUM_RAN);
	printf("Number of tests passed: %d\n", NUM_PASSED);
	printf("Number of tests failed: %d\n", NUM_FAILED);
}

/* Helpful functions */
// TODO: Can probably make this a macro instead, but will need to investigate this
void init_matrix_with_values_4(Matrix *m, float values[][4])
{
	matrix_init(m, 4);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			matrix_set(m, i, j, values[i][j]);
}

void init_matrix_with_values_3(Matrix *m, float values[][3])
{
	matrix_init(m, 3);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			matrix_set(m, i, j, values[i][j]);
}

void init_matrix_with_values_2(Matrix *m, float values[][2])
{
	matrix_init(m, 2);
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			matrix_set(m, i, j, values[i][j]);
}


/* Tests */

void constructing_and_inspecting_a_4x4_matrix()
{
	Matrix m;
	float values[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f},
						{5.5f, 6.5f, 7.5f, 8.5f},
						{9.0f, 10.0f, 11.0f, 12.0f},
						{13.5f, 14.5f, 15.5f, 16.5f}};
	init_matrix_with_values_4(&m, values);

	if (float_equal(matrix_get(&m, 0, 0), 1.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 0, 3), 4.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 1, 0), 5.5f))
		return test_failed();
	if (float_equal(matrix_get(&m, 1, 2), 7.5f))
		return test_failed();
	if (float_equal(matrix_get(&m, 2, 2), 11.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 3, 0), 13.5f))
		return test_failed();
	if (float_equal(matrix_get(&m, 3, 2), 15.5f))
		return test_failed();
	
	test_passed();
}

void a_2x2_matrix_ought_to_be_representable()
{
	Matrix m;
	float values[2][2] = {{-3, 5},
						{1, -2}};
	init_matrix_with_values_2(&m, values);

	if (float_equal(matrix_get(&m, 0, 0), -3.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 0, 1), 5.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 1, 0), 1.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 1, 1), -2.0f))
		return test_failed();
	
	test_passed();
}

void a_3x3_matrix_ought_to_be_representable()
{
	Matrix m;
	float values[3][3] = {{-3, 5, 0},
						{1, -2, -7},
						{0, 1, 1}};
	init_matrix_with_values_3(&m, values);

	if (float_equal(matrix_get(&m, 0, 0), -3.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 1, 1), -2.0f))
		return test_failed();
	if (float_equal(matrix_get(&m, 2, 2), 1.0f))
		return test_failed();
	
	test_passed();
}

void matrix_equality_with_identical_matrices()
{
	Matrix a, b;
	float values_a[4][4] = {{1, 2, 3, 4},
						  {5, 6, 7, 8},
						  {9, 8, 7, 6},
						  {5, 4, 3, 2}};
	float values_b[4][4] = {{1, 2, 3, 4},
						  {5, 6, 7, 8},
						  {9, 8, 7, 6},
						  {5, 4, 3, 2}};
	init_matrix_with_values_4(&a, values_a);
	init_matrix_with_values_4(&b, values_b);

	if (matrix_equal(&a, &b))
		return test_failed();
	return test_passed();
}


void matrix_equality_with_different_matrices()
{
	Matrix a, b;
	float values_a[4][4] = {{1, 2, 3, 4},
						  {5, 6, 7, 8},
						  {9, 8, 7, 6},
						  {5, 4, 3, 2}};
	float values_b[4][4] = {{2, 3, 4, 5},
						  {6, 7, 8, 9},
						  {8, 7, 6, 5},
						  {4, 3, 2, 1}};
	
	init_matrix_with_values_4(&a, values_a);
	init_matrix_with_values_4(&b, values_b);

	if (matrix_equal(&a, &b))
		return test_passed();
	test_failed();
}

void multiplying_two_matrices()
{
	Matrix a, b, expected, result;
	float values_a[4][4] = {{1, 2, 3, 4},
						  {5, 6, 7, 8},
						  {9, 8, 7, 6},
						  {5, 4, 3, 2}};
	float values_b[4][4] = {{-2, 1, 2, 3},
						  {3, 2, 1, -1},
						  {4, 3, 6, 5},
						  {1, 2, 7, 8}};
	float expected_result[4][4] = {{20, 22, 50, 48},
								 {44, 54, 114, 108},
								 {40, 58, 110, 102},
								 {16, 26, 46, 42}};
	init_matrix_with_values_4(&a, values_a);
	init_matrix_with_values_4(&b, values_b);
	init_matrix_with_values_4(&expected, expected_result);
	matrix_mul(&result, &a, &b);

	if (matrix_equal(&expected, &result))
		return test_failed();
	test_passed();
}

void a_matrix_multiplied_by_a_tuple()
{
	Matrix a;
	Tuple b, result, expected;

	float values[4][4] = {{1, 2, 3, 4},
						  {2, 4, 4, 2},
						  {8, 6, 4, 1},
						  {0, 0, 0, 1}};
	tuple_init(&b, 1, 2, 3, 1);
	tuple_init(&expected, 18, 24, 33, 1);
	init_matrix_with_values_4(&a, values);

	matrix_mul_tuple(&result, &a, &b);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void multiplying_a_matrix_by_the_identity_matrix()
{
	Matrix a, identity, result;
	float values[4][4] = {{0, 1, 2, 4},
	 					  {1, 2, 4, 8},
						  {2, 4, 8, 16},
						  {4, 8, 16, 32}};
	init_matrix_with_values_4(&a, values);
	matrix_identity(&identity);

	matrix_mul(&result, &a, &identity);

	if (matrix_equal(&a, &result))
		return test_failed();
	
	test_passed();
}

void multiplying_the_identity_matrix_by_a_tuple()
{
	Matrix identity;
	Tuple a, result;

	tuple_init(&a, 1, 2, 3, 4);
	matrix_identity(&identity);

	matrix_mul_tuple(&result, &identity, &a);
	if (tuple_equal(&a, &result))
		return test_failed();
	
	test_passed();
}

void transposing_a_matrix()
{
	Matrix a, result, expected;
	float values[4][4] = {{0, 9, 3, 0},
						  {9, 8, 0, 8},
						  {1, 8, 5, 3},
						  {0, 0, 5, 8}};
	init_matrix_with_values_4(&a, values);

	float values_expected[4][4] = {{0, 9, 1, 0},
			  {9, 8, 8, 0},
			  {3, 0, 5, 5},
			  {0, 8, 3, 8}};
	init_matrix_with_values_4(&expected, values_expected);

	matrix_transpose(&result, &a);
	if (matrix_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void transposing_the_identity_matrix()
{
	Matrix identity, a;
	matrix_identity(&identity);
	matrix_transpose(&a, &identity);

	if (matrix_equal(&a, &identity))
		return test_failed();
	test_passed();
}

void calculating_the_determinant_of_a_2x2_matrix()
{
	Matrix a;
	float values[2][2] = {{1, 5},
						  {-3, 2}};
	init_matrix_with_values_2(&a, values);
	float expected = 17;
	float result = matrix_determinant(&a);

	if (float_equal(expected, result))
		return test_failed();
	test_passed();
}

void a_submatrix_of_a_3x3_matrix_is_a_2x2_matrix()
{
	Matrix a, result, expected;
	float values[3][3] = {{1, 5, 0},
						  {-3, 2, 7},
						  {0, 6, -3}};
	init_matrix_with_values_3(&a, values);
	
	float expected_values[2][2] = {{-3, 2},
								   {0, 6}};
	init_matrix_with_values_2(&expected, expected_values);

	matrix_submatrix(&result, &a, 0, 2);

	if (matrix_equal(&expected, &result))
		return test_failed();
	test_passed();
}

void a_submatrix_of_a_4x4_matrix_is_a_3x3_matrix()
{
	Matrix a, result, expected;
	float values[4][4] = {{-6, 1, 1, 6},
						  {-8, 5, 8, 6},
						  {-1, 0, 8, 2},
						  {-7, 1, -1, 1}};
	init_matrix_with_values_4(&a, values);
	float expected_values[3][3] = {{-6, 1, 6},
								   {-8, 8, 6},
								   {-7, -1, 1}};
	init_matrix_with_values_3(&expected, expected_values);

	matrix_submatrix(&result, &a, 2, 1);

	if (matrix_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void calculating_a_minor_of_a_3x3_matrix()
{
	Matrix a, b;
	float result, expected;

	float values[3][3] = {{3, 5, 0},
					 	  {2, -1, -7},
						  {6, -1, 5}};
	init_matrix_with_values_3(&a, values);
	matrix_submatrix(&b, &a, 1, 0);

	expected = 25;
	result = matrix_determinant(&b);
	if (float_equal(expected, result))
		return test_failed();
	
	result = matrix_minor(&a, 1, 0);
	if (float_equal(expected, result))
		return test_failed();
	
	test_passed();
}

void calculating_a_cofactor_of_a_3x3_matrix()
{
	Matrix a;
	float values[3][3] = {{3, 5, 0},
						  {2, -1, -7},
						  {6, -1, 5}};
	init_matrix_with_values_3(&a, values);

	float result = matrix_minor(&a, 0, 0);
	if (float_equal(-12, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 0, 0);
	if (float_equal(-12, result))
		return test_failed();
	
	result = matrix_minor(&a, 1, 0);
	if (float_equal(25, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 1, 0);
	if (float_equal(-25, result))
		return test_failed();
	
	test_passed();
}

void calculating_the_determinant_of_a_3x3_matrix()
{
	Matrix a;
	float values[3][3] = {{1, 2, 6},
						  {-5, 8, -4},
						  {2, 6, 4}};
	init_matrix_with_values_3(&a, values);

	float result = matrix_cofactor(&a, 0, 0);
	if (float_equal(56, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 0, 1);
	if (float_equal(12, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 0, 2);
	if (float_equal(-46, result))
		return test_failed();
	
	result = matrix_determinant(&a);
	if (float_equal(-196, result))
		return test_failed();
	
	test_passed();
}

void calculating_the_determinant_of_a_4x4_matrix()
{
	Matrix a;
	float values[4][4] = {{-2, -8, 3, 5},
						  {-3, 1, 7, 3},
						  {1, 2, -9, 6},
						  {-6, 7, 7, -9}};
	init_matrix_with_values_4(&a, values);

	float result = matrix_cofactor(&a, 0, 0);
	if (float_equal(690, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 0, 1);
	if (float_equal(447, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 0, 2);
	if (float_equal(210, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 0, 3);
	if (float_equal(51, result))
		return test_failed();
	
	result = matrix_determinant(&a);
	if (float_equal(-4071, result))
		return test_failed();
	
	test_passed();
}

void testing_an_invertible_matrix_for_invertibility()
{
	Matrix a;
	float values[4][4] = {{6, 4, 4, 4},
						  {5, 5, 7, 6},
						  {4, -9, 3, -7},
						  {9, 1, 7, -6}};
	init_matrix_with_values_4(&a, values);

	float result = matrix_determinant(&a);
	if (float_equal(0, result))
		return test_passed();
	
	return test_failed();
}

void testing_a_noninvertible_matrix_for_invertibility()
{
	Matrix a;
	float values[4][4] = {{-4, 2, -2, -3},
						  {9, 6, 2, 6},
						  {0, -5, 1, -5},
						  {0, 0, 0, 0}};
	init_matrix_with_values_4(&a, values);

	float result = matrix_determinant(&a);
	if (float_equal(0, result))
		return test_failed();
	
	test_passed();
}

void calculating_the_inverse_of_a_matrix()
{
	Matrix a, b, expected;
	float values[4][4] = {{-5, 2, 6, -8},
						  {1, -5, 1, 8},
						  {7, 7, -6, -7},
						  {1, -3, 7, 4}};
	init_matrix_with_values_4(&a, values);

	float expected_values[4][4] = {{0.21805, 0.45113, 0.24060, -0.04511},
								   {-0.80827, -1.45677, -0.44361, 0.52068},
								   {-0.07895, -0.22368, -0.05263, 0.19737},
								   {-0.52256, -0.81391, -0.30075, 0.30639}};
	init_matrix_with_values_4(&expected, expected_values);

	int error = matrix_inverse(&b, &a);
	if (error)
		return test_failed();

	float result = matrix_determinant(&a);
	if (!float_equal(0, result))
		return test_failed();
	
	result = matrix_cofactor(&a, 2, 3);
	if (float_equal(-160, result))
		return test_failed();
	
	result = -160.0/532.0;
	if (float_equal(result, matrix_get(&b, 3, 2)))
		return test_failed();
	
	result = matrix_cofactor(&a, 3, 2);
	if (float_equal(105, result))
		return test_failed();

	result = 105.0/532.0;
	if (float_equal(result, matrix_get(&b, 2, 3)))
		return test_failed();

	if (matrix_equal(&expected, &b))
		return test_failed();

	test_passed();
}

void calculating_the_inverse_of_another_matrix()
{
	Matrix a, expected, result;
	float values[4][4] = {{8, -5, 9, 2},
						  {7, 5, 6, 1},
						  {-6, 0, 9, 6},
						  {-3, 0, -9, -4}};
	init_matrix_with_values_4(&a, values);

	float expected_values[4][4] = {{-0.15385, -0.15385, -0.28205, -0.53846},
								   {-0.07692, 0.12308, 0.02564, 0.03077},
								   {0.35897, 0.35897, 0.43590, 0.92308},
								   {-0.69231, -0.69231, -0.76923, -1.92308}};
	init_matrix_with_values_4(&expected, expected_values);
	
	matrix_inverse(&result, &a);

	if (matrix_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void calculating_the_inverse_of_a_third_matrix()
{
	Matrix a, expected, result;
	float values[4][4] = {{9, 3, 0, 9},
						  {-5, -2, -6, -3},
						  {-4, 9, 6, 4},
						  {-7, 6, 6, 2}};
	init_matrix_with_values_4(&a, values);

	float expected_values[4][4] = {{-0.04074, -0.0778, 0.14444, -0.22222},
								   {-0.07778, 0.03333, 0.36667, -0.33333},
								   {-0.02901, -0.14630, -0.10923, 0.12963},
								   {0.17778, 0.06667, -0.26667, 0.33333}};
	init_matrix_with_values_4(&expected, expected_values);

	matrix_inverse(&result, &a);

	if (matrix_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void multiplying_a_product_by_its_inverse()
{
	Matrix a, b, c, inverse, result;
	float values_a[4][4] = {{3, -9, 7, 3},
							{3, -8, 1, -9},
							{-4, 4, 4, 1},
							{-6, 5, -1, 1}};
	init_matrix_with_values_4(&a, values_a);

	float values_b[4][4] = {{8, 2, 2, 2},
							{3, -1, 7, 0},
							{7, 0, 5, 4},
							{6, -2, 0, 5}};
	init_matrix_with_values_4(&b, values_b);

	matrix_mul(&c, &a, &b);
	matrix_inverse(&inverse, &b);
	matrix_mul(&result, &c, &inverse);

	if (matrix_equal(&a, &result))
		return test_failed();
	
	return test_passed();
}

int main()
{
	constructing_and_inspecting_a_4x4_matrix();
	a_2x2_matrix_ought_to_be_representable();
	a_3x3_matrix_ought_to_be_representable();
	matrix_equality_with_identical_matrices();
	matrix_equality_with_different_matrices();
	multiplying_two_matrices();
	a_matrix_multiplied_by_a_tuple();
	multiplying_a_matrix_by_the_identity_matrix();
	multiplying_the_identity_matrix_by_a_tuple();
	transposing_a_matrix();
	transposing_the_identity_matrix();
	calculating_the_determinant_of_a_2x2_matrix();
	a_submatrix_of_a_3x3_matrix_is_a_2x2_matrix();
	a_submatrix_of_a_4x4_matrix_is_a_3x3_matrix();
	calculating_a_minor_of_a_3x3_matrix();
	calculating_a_cofactor_of_a_3x3_matrix();
	calculating_the_determinant_of_a_3x3_matrix();
	calculating_the_determinant_of_a_4x4_matrix();
	testing_an_invertible_matrix_for_invertibility();
	testing_a_noninvertible_matrix_for_invertibility();
	calculating_the_inverse_of_a_matrix();
	calculating_the_inverse_of_another_matrix();
	calculating_the_inverse_of_a_third_matrix();
	multiplying_a_product_by_its_inverse();
	test_results();
	return 0;
}


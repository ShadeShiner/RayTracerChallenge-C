#include <stdio.h>
#include <test_library.h>
#include "tuple.h"
#include "matrix.h"


void constructing_and_inspecting_a_4x4_matrix()
{
	Matrix m[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f},
					  {5.5f, 6.5f, 7.5f, 8.5f},
					  {9.0f, 10.0f, 11.0f, 12.0f},
					  {13.5f, 14.5f, 15.5f, 16.5f}};

	if (float_equal(matrix_get(array_mem(m), 0, 0, 4), 1.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 0, 3, 4), 4.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 1, 0, 4), 5.5f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 1, 2, 4), 7.5f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 2, 2, 4), 11.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 3, 0, 4), 13.5f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 3, 2, 4), 15.5f))
		return test_failed();
	
	test_passed();
}


void a_2x2_matrix_ought_to_be_representable()
{
	Matrix m[2][2] = {{-3, 5},
					  {1, -2}};

	if (float_equal(matrix_get(array_mem(m), 0, 0, 2), -3.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 0, 1, 2), 5.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 1, 0, 2), 1.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 1, 1, 2), -2.0f))
		return test_failed();
	
	test_passed();
}


void a_3x3_matrix_ought_to_be_representable()
{
	Matrix m[3][3] = {{-3, 5, 0},
						{1, -2, -7},
						{0, 1, 1}};

	if (float_equal(matrix_get(array_mem(m), 0, 0, 3), -3.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 1, 1, 3), -2.0f))
		return test_failed();
	if (float_equal(matrix_get(array_mem(m), 2, 2, 3), 1.0f))
		return test_failed();
	
	test_passed();
}


void matrix_equality_with_identical_matrices()
{
	Matrix a[4][4] = {{1, 2, 3, 4},
					  {5, 6, 7, 8},
					  {9, 8, 7, 6},
					  {5, 4, 3, 2}};
	Matrix b[4][4] = {{1, 2, 3, 4},
					  {5, 6, 7, 8},
					  {9, 8, 7, 6},
					  {5, 4, 3, 2}};

	if (matrix_equal(array_mem(a), array_mem(b), 4))
		return test_failed();
	
	test_passed();
}


void matrix_equality_with_different_matrices()
{
	Matrix a[4][4] = {{1, 2, 3, 4},
					  {5, 6, 7, 8},
					  {9, 8, 7, 6},
					  {5, 4, 3, 2}};
	Matrix b[4][4] = {{2, 3, 4, 5},
					  {6, 7, 8, 9},
					  {8, 7, 6, 5},
					  {4, 3, 2, 1}};

	if (matrix_equal(array_mem(a), array_mem(b), 4))
		return test_passed();
	
	test_failed();
}


void multiplying_two_matrices()
{
	Matrix result[4][4];
	Matrix a[4][4] = {{1, 2, 3, 4},
					  {5, 6, 7, 8},
					  {9, 8, 7, 6},
					  {5, 4, 3, 2}};
	Matrix b[4][4] = {{-2, 1, 2, 3},
					  {3, 2, 1, -1},
					  {4, 3, 6, 5},
					  {1, 2, 7, 8}};
	Matrix expected[4][4] = {{20, 22, 50, 48},
							 {44, 54, 114, 108},
							 {40, 58, 110, 102},
							 {16, 26, 46, 42}};
	matrix_mul(array_mem(result), array_mem(a), array_mem(b), 4);

	if (matrix_equal(array_mem(expected), array_mem(result), 4))
		return test_failed();
	
	test_passed();
}


void a_matrix_multiplied_by_a_tuple()
{
	Tuple b, result, expected;

	Matrix a[4][4] = {{1, 2, 3, 4},
						  {2, 4, 4, 2},
						  {8, 6, 4, 1},
						  {0, 0, 0, 1}};
	tuple_init(&b, 1, 2, 3, 1);
	tuple_init(&expected, 18, 24, 33, 1);

	matrix_mul_tuple(&result, array_mem(a), &b);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed()
}


void multiplying_a_matrix_by_the_identity_matrix()
{
	Matrix identity[4][4], result[4][4];
	Matrix a[4][4] = {{0, 1, 2, 4},
	 				  {1, 2, 4, 8},
					  {2, 4, 8, 16},
					  {4, 8, 16, 32}};
	matrix_identity(array_mem(identity), 4);

	matrix_mul(array_mem(result), array_mem(a), array_mem(identity), 4);

	if (matrix_equal(array_mem(a), array_mem(result), 4))
		return test_failed();
	
	test_passed();
}


void multiplying_the_identity_matrix_by_a_tuple()
{
	Matrix identity[4][4];
	Tuple a, result;

	tuple_init(&a, 1, 2, 3, 4);
	matrix_identity(array_mem(identity), 4);

	matrix_mul_tuple(&result, array_mem(identity), &a);
	if (tuple_equal(&a, &result))
		return test_failed();
	
	test_passed();
}


void transposing_a_matrix()
{
	Matrix result[4][4];
	Matrix a[4][4] = {{0, 9, 3, 0},
					  {9, 8, 0, 8},
					  {1, 8, 5, 3},
					  {0, 0, 5, 8}};

	Matrix expected[4][4] = {{0, 9, 1, 0},
			  				 {9, 8, 8, 0},
			  				 {3, 0, 5, 5},
			  				 {0, 8, 3, 8}};

	matrix_transpose(array_mem(result), array_mem(a), 4);
	if (matrix_equal(array_mem(expected), array_mem(result), 4))
		return test_failed();
	
	test_passed();
}


void transposing_the_identity_matrix()
{
	Matrix identity[4][4], a[4][4];
	matrix_identity(array_mem(identity), 4);
	matrix_transpose(array_mem(a), array_mem(identity), 4);

	if (matrix_equal(array_mem(a), array_mem(identity), 4))
		return test_failed();
	
	test_passed()
}


void a_submatrix_of_a_3x3_matrix_is_a_2x2_matrix()
{
	Matrix result[2][2];
	Matrix a[3][3] = {{1, 5, 0},
						  {-3, 2, 7},
						  {0, 6, -3}};
	
	float expected[2][2] = {{-3, 2},
							{0, 6}};

	matrix_submatrix(array_mem(result), array_mem(a), 0, 2, 3);

	if (matrix_equal(array_mem(expected), array_mem(result), 2))
		return test_failed();
	
	test_passed();
}


void a_submatrix_of_a_4x4_matrix_is_a_3x3_matrix()
{
	Matrix result[4][4];
	Matrix a[4][4] = {{-6, 1, 1, 6},
					  {-8, 5, 8, 6},
					  {-1, 0, 8, 2},
					  {-7, 1, -1, 1}};
	Matrix expected[3][3] = {{-6, 1, 6},
							 {-8, 8, 6},
							 {-7, -1, 1}};

	matrix_submatrix(array_mem(result), array_mem(a), 2, 1, 4);

	if (matrix_equal(array_mem(expected), array_mem(result), 3))
		return test_failed();
	
	test_passed();
}


void calculating_the_determinant_of_a_2x2_matrix()
{
	Matrix a[2][2] = {{1, 5},
					  {-3, 2}};
	float expected = 17;
	float result = matrix_determinant(array_mem(a), 2);

	if (float_equal(expected, result))
		return test_failed();
	
	test_passed();
}


void calculating_a_minor_of_a_3x3_matrix()
{
	float result, expected;
	Matrix b[2][2];
	Matrix a[3][3] = {{3, 5, 0},
					  {2, -1, -7},
					  {6, -1, 5}};
	matrix_submatrix(array_mem(b), array_mem(a), 1, 0, 3);

	expected = 25;
	result = matrix_determinant(array_mem(b), 2);
	if (float_equal(expected, result))
		return test_failed();
	
	result = matrix_minor(array_mem(a), 1, 0, 3);
	if (float_equal(expected, result))
		return test_failed();
	
	test_passed();
}


void calculating_a_cofactor_of_a_3x3_matrix()
{
	Matrix a[3][3] = {{3, 5, 0},
					  {2, -1, -7},
					  {6, -1, 5}};

	float result = matrix_minor(array_mem(a), 0, 0, 3);
	if (float_equal(-12, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 0, 0, 3);
	if (float_equal(-12, result))
		return test_failed();
	
	result = matrix_minor(array_mem(a), 1, 0, 3);
	if (float_equal(25, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 1, 0, 3);
	if (float_equal(-25, result))
		return test_failed();
	
	test_passed();
}


void calculating_the_determinant_of_a_3x3_matrix()
{
	Matrix a[3][3] = {{1, 2, 6},
					  {-5, 8, -4},
					  {2, 6, 4}};

	float result = matrix_cofactor(array_mem(a), 0, 0, 3);
	if (float_equal(56, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 0, 1, 3);
	if (float_equal(12, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 0, 2, 3);
	if (float_equal(-46, result))
		return test_failed();
	
	result = matrix_determinant(array_mem(a), 3);
	if (float_equal(-196, result))
		return test_failed();
	
	test_passed();
}


void calculating_the_determinant_of_a_4x4_matrix()
{
	Matrix a[4][4] = {{-2, -8, 3, 5},
					  {-3, 1, 7, 3},
					  {1, 2, -9, 6},
					  {-6, 7, 7, -9}};

	float result = matrix_cofactor(array_mem(a), 0, 0, 4);
	if (float_equal(690, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 0, 1, 4);
	if (float_equal(447, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 0, 2, 4);
	if (float_equal(210, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 0, 3, 4);
	if (float_equal(51, result))
		return test_failed();
	
	result = matrix_determinant(array_mem(a), 4);
	if (float_equal(-4071, result))
		return test_failed();
	
	test_passed();
}


void testing_an_invertible_matrix_for_invertibility()
{
	Matrix a[4][4] = {{6, 4, 4, 4},
					  {5, 5, 7, 6},
					  {4, -9, 3, -7},
					  {9, 1, 7, -6}};

	float result = matrix_determinant(array_mem(a), 4);
	if (float_equal(0, result))
		return test_passed();
	
	test_failed();
}


void testing_a_noninvertible_matrix_for_invertibility()
{
	Matrix a[4][4] = {{-4, 2, -2, -3},
						  {9, 6, 2, 6},
						  {0, -5, 1, -5},
						  {0, 0, 0, 0}};

	float result = matrix_determinant(array_mem(a), 4);
	if (float_equal(0, result))
		return test_failed();
	
	test_passed();
}


void calculating_the_inverse_of_a_matrix()
{
	Matrix a[4][4] = {{-5, 2, 6, -8},
					  {1, -5, 1, 8},
					  {7, 7, -6, -7},
					  {1, -3, 7, 4}};

	Matrix expected[4][4] = {{0.21805, 0.45113, 0.24060, -0.04511},
							 {-0.80827, -1.45677, -0.44361, 0.52068},
							 {-0.07895, -0.22368, -0.05263, 0.19737},
							 {-0.52256, -0.81391, -0.30075, 0.30639}};

	Matrix b[4][4];
	int error = matrix_inverse(array_mem(b), array_mem(a), 4);
	if (error)
		return test_failed();

	float result = matrix_determinant(array_mem(a), 4);
	if (!float_equal(0, result))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 2, 3, 4);
	if (float_equal(-160, result))
		return test_failed();
	
	result = -160.0/532.0;
	if (float_equal(result, matrix_get(array_mem(b), 3, 2, 4)))
		return test_failed();
	
	result = matrix_cofactor(array_mem(a), 3, 2, 4);
	if (float_equal(105, result))
		return test_failed();

	result = 105.0/532.0;
	if (float_equal(result, matrix_get(array_mem(b), 2, 3, 4)))
		return test_failed();

	if (matrix_equal(array_mem(expected), array_mem(b), 4))
		return test_failed();

	test_passed();
}


void calculating_the_inverse_of_another_matrix()
{
	Matrix result[4][4];
	Matrix a[4][4] = {{8, -5, 9, 2},
					  {7, 5, 6, 1},
					  {-6, 0, 9, 6},
					  {-3, 0, -9, -4}};

	Matrix expected[4][4] = {{-0.15385, -0.15385, -0.28205, -0.53846},
							 {-0.07692, 0.12308, 0.02564, 0.03077},
							 {0.35897, 0.35897, 0.43590, 0.92308},
							 {-0.69231, -0.69231, -0.76923, -1.92308}};
	
	matrix_inverse(array_mem(result), array_mem(a), 4);

	if (matrix_equal(array_mem(expected), array_mem(result), 4))
		return test_failed();
	
	test_passed();
}


void calculating_the_inverse_of_a_third_matrix()
{
	Matrix result[4][4];
	Matrix a[4][4] = {{9, 3, 0, 9},
					  {-5, -2, -6, -3},
					  {-4, 9, 6, 4},
					  {-7, 6, 6, 2}};

	Matrix expected[4][4] = {{-0.04074, -0.07778, 0.14444, -0.22222},
							 {-0.07778, 0.03333, 0.36667, -0.33333},
							 {-0.02901, -0.14630, -0.10926, 0.12963},
							 {0.17778, 0.06667, -0.26667, 0.33333}};

	matrix_inverse(array_mem(result), array_mem(a), 4);

	if (matrix_equal(array_mem(expected), array_mem(result), 4))
		return test_failed();
	
	test_passed();
}


void multiplying_a_product_by_its_inverse()
{
	Matrix c[4][4], inverse[4][4], result[4][4];
	Matrix a[4][4] = {{3, -9, 7, 3},
					  {3, -8, 1, -9},
					  {-4, 4, 4, 1},
					  {-6, 5, -1, 1}};

	Matrix b[4][4] = {{8, 2, 2, 2},
					  {3, -1, 7, 0},
					  {7, 0, 5, 4},
					  {6, -2, 0, 5}};

	matrix_mul(array_mem(c), array_mem(a), array_mem(b), 4);
	matrix_inverse(array_mem(inverse), array_mem(b), 4);
	matrix_mul(array_mem(result), array_mem(c), array_mem(inverse), 4);

	if (matrix_equal(array_mem(a), array_mem(result), 4))
		return test_failed();
	
	test_passed();
}


int main()
{
	test_header();
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


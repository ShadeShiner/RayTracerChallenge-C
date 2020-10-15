#include <stdio.h>
#include <math.h>
#include <test_library.h>
#include <matrix.h>
#include <tuple.h>

void multiplying_by_a_translation_matrix()
{
	Matrix transform;
	matrix_translation(&transform, 5, -3, 2);

	Point p, result, expected;
	point_init(&p, -3, 4, 5);
	point_init(&expected, 2, 1, 7);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void multiplying_by_the_inverse_of_a_translations_matrix()
{
	Matrix transform, inverse;
	matrix_translation(&transform, 5, -3, 2);
	matrix_inverse(&inverse, &transform);

	Point p, result, expected;
	point_init(&p, -3, 4, 5);
	point_init(&expected, -8, 7, 3);

	matrix_mul_tuple(&result, &inverse, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void translation_does_not_affect_vectors()
{
	Matrix transform;
	matrix_translation(&transform, 5, -3, 2);

	Vector v, result;
	vector_init(&v, -3, 4, 5);

	matrix_mul_tuple(&result, &transform, &v);
	if (tuple_equal(&v, &result))
		return test_failed();
	
	test_passed();
}

void a_scaling_matrix_applied_to_a_point()
{
	Matrix transform;
	matrix_scaling(&transform, 2, 3, 4);

	Point p, result, expected;
	point_init(&p, -4, 6, 8);
	point_init(&expected, -8, 18, 32);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_scaling_matrix_applied_to_a_vector()
{
	Matrix transform;
	matrix_scaling(&transform, 2, 3, 4);

	Vector v, result, expected;
	vector_init(&v, -4, 6, 8);
	vector_init(&expected, -8, 18, 32);

	matrix_mul_tuple(&result, &transform, &v);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void multiplying_by_the_inverse_of_a_scaling_matrix()
{
	Matrix transform, inverse;
	matrix_scaling(&transform, 2, 3, 4);
	matrix_inverse(&inverse, &transform);

	Vector v, result, expected;
	vector_init(&v, -4, 6, 8);
	vector_init(&expected, -2, 2, 2);

	matrix_mul_tuple(&result, &inverse, &v);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void rotating_a_point_around_the_x_axis()
{
	Point p, result_one, result_two, expected_one, expected_two;
	Matrix half_quarter, full_quarter;

	point_init(&p, 0, 1, 0);
	matrix_rotation_x(&half_quarter, M_PI_4);
	matrix_rotation_x(&full_quarter, M_PI_2);

	point_init(&expected_one, 0, sqrtf(2)/2, sqrtf(2)/2);
	point_init(&expected_two, 0, 0, 1);

	matrix_mul_tuple(&result_one, &half_quarter, &p);
	if (tuple_equal(&expected_one, &result_one))
		return test_failed();

	matrix_mul_tuple(&result_two, &full_quarter, &p);
	if (tuple_equal(&expected_two, &expected_one))
		return test_failed();
	
	test_passed();
}

void inverse_of_an_x_rotation_rotates_in_the_opposite_direction()
{
	Point p, result, expected;
	Matrix half_quarter, inverse;

	point_init(&p, 0, 1, 0);
	point_init(&expected, 0, sqrtf(2)/2, -sqrtf(2)/2);
	matrix_rotation_x(&half_quarter, M_PI_4);
	matrix_inverse(&inverse, &half_quarter);

	matrix_mul_tuple(&result, &inverse, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void rotating_a_point_around_the_y_axis()
{
	Point p, result_one, result_two, expected_one, expected_two;
	Matrix half_quarter, full_quarter;

	point_init(&p, 0, 0, 1);
	point_init(&expected_one, sqrtf(2)/2, 0, sqrtf(2)/2);
	point_init(&expected_two, 1, 0, 0);

	matrix_rotation_y(&half_quarter, M_PI_4);
	matrix_rotation_y(&full_quarter, M_PI_2);

	matrix_mul_tuple(&result_one, &half_quarter, &p);
	if (tuple_equal(&expected_one, &result_one))
		return test_failed();
	
	matrix_mul_tuple(&result_two, &full_quarter, &p);
	if (tuple_equal(&expected_two, &result_two))
		return test_failed();
	
	test_passed();
}

void rotating_a_point_around_the_z_axis()
{
	Point p, result_one, result_two, expected_one, expected_two;
	Matrix half_quarter, full_quarter;

	point_init(&p, 0, 1, 0);
	point_init(&expected_one, -sqrtf(2)/2, sqrtf(2)/2, 0);
	point_init(&expected_two, -1, 0, 0);

	matrix_rotation_z(&half_quarter, M_PI_4);
	matrix_rotation_z(&full_quarter, M_PI_2);

	matrix_mul_tuple(&result_one, &half_quarter, &p);
	if (tuple_equal(&expected_one, &result_one))
		return test_failed();
	
	matrix_mul_tuple(&result_two, &full_quarter, &p);
	if (tuple_equal(&expected_two, &result_two))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_x_in_proportion_to_y()
{
	Matrix transform;
	Point p, result, expected;

	matrix_shearing(&transform, 1, 0, 0, 0, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 5, 3, 4);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_x_in_proportion_to_z()
{
	Matrix transform;
	Point p, result, expected;

	matrix_shearing(&transform, 0, 1, 0, 0, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 6, 3, 4);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_y_in_proportion_to_x()
{
	Matrix transform;
	Point p, result, expected;

	matrix_shearing(&transform, 0, 0, 1, 0, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 5, 4);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_y_in_proportion_to_z()
{
	Matrix transform;
	Point p, result, expected;

	matrix_shearing(&transform, 0, 0, 0, 1, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 7, 4);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_z_in_proportion_to_x()
{
	Matrix transform;
	Point p, result, expected;

	matrix_shearing(&transform, 0, 0, 0, 0, 1, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 3, 6);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_z_in_proportion_to_y()
{
	Matrix transform;
	Point p, result, expected;

	matrix_shearing(&transform, 0, 0, 0, 0, 0, 1);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 3, 7);

	matrix_mul_tuple(&result, &transform, &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void individual_transformations_are_applied_in_sequence()
{
	Matrix A, B, C;
	Point p, p2, p3, p4;
	Point expected1, expected2, expected3;

	point_init(&p, 1, 0, 1);
	matrix_rotation_x(&A, M_PI_2);
	matrix_scaling(&B, 5, 5, 5);
	matrix_translation(&C, 10, 5, 7);

	point_init(&expected1, 1, -1, 0);
	point_init(&expected2, 5, -5, 0);
	point_init(&expected3, 15, 0, 7);

	matrix_mul_tuple(&p2, &A, &p);
	if (tuple_equal(&expected1, &p2))
		return test_failed();
	
	matrix_mul_tuple(&p3, &B, &p2);
	if (tuple_equal(&expected2, &p3))
		return test_failed();

	matrix_mul_tuple(&p4, &C, &p3);
	if (tuple_equal(&expected3, &p4))
		return test_failed();
	
	test_passed();
}

int main()
{
	test_header();
	multiplying_by_a_translation_matrix();
	multiplying_by_the_inverse_of_a_translations_matrix();
	translation_does_not_affect_vectors();
	a_scaling_matrix_applied_to_a_point();
	a_scaling_matrix_applied_to_a_vector();
	multiplying_by_the_inverse_of_a_scaling_matrix();
	rotating_a_point_around_the_x_axis();
	inverse_of_an_x_rotation_rotates_in_the_opposite_direction();
	rotating_a_point_around_the_y_axis();
	rotating_a_point_around_the_z_axis();
	a_shearing_transformation_moves_x_in_proportion_to_y();
	a_shearing_transformation_moves_x_in_proportion_to_z();
	a_shearing_transformation_moves_y_in_proportion_to_x();
	a_shearing_transformation_moves_y_in_proportion_to_z();
	a_shearing_transformation_moves_z_in_proportion_to_x();
	a_shearing_transformation_moves_z_in_proportion_to_y();
	individual_transformations_are_applied_in_sequence();
	test_results();
	return 0;
}


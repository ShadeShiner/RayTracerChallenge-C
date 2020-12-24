#include <stdio.h>
#include <math.h>
#include <test_library.h>
#include <matrix.h>
#include <tuple.h>

void multiplying_by_a_translation_matrix()
{
	Matrix transform[4][4];
	matrix_translation(array_mem(transform), 5, -3, 2);

	Point p, result, expected;
	point_init(&p, -3, 4, 5);
	point_init(&expected, 2, 1, 7);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void multiplying_by_the_inverse_of_a_translations_matrix()
{
	Matrix transform[4][4], inverse[4][4];
	matrix_translation(array_mem(transform), 5, -3, 2);
	matrix_inverse(array_mem(inverse), array_mem(transform), 4);

	Point p, result, expected;
	point_init(&p, -3, 4, 5);
	point_init(&expected, -8, 7, 3);

	matrix_mul_tuple(&result, array_mem(inverse), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void translation_does_not_affect_vectors()
{
	Matrix transform[4][4];
	matrix_translation(array_mem(transform), 5, -3, 2);

	Vector v, result;
	vector_init(&v, -3, 4, 5);

	matrix_mul_tuple(&result, array_mem(transform), &v);
	if (tuple_equal(&v, &result))
		return test_failed();
	
	test_passed();
}

void a_scaling_matrix_applied_to_a_point()
{
	Matrix transform[4][4];
	matrix_scaling(array_mem(transform), 2, 3, 4);

	Point p, result, expected;
	point_init(&p, -4, 6, 8);
	point_init(&expected, -8, 18, 32);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_scaling_matrix_applied_to_a_vector()
{
	Matrix transform[4][4];
	matrix_scaling(array_mem(transform), 2, 3, 4);

	Vector v, result, expected;
	vector_init(&v, -4, 6, 8);
	vector_init(&expected, -8, 18, 32);

	matrix_mul_tuple(&result, array_mem(transform), &v);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void multiplying_by_the_inverse_of_a_scaling_matrix()
{
	Matrix transform[4][4], inverse[4][4];
	matrix_scaling(array_mem(transform), 2, 3, 4);
	matrix_inverse(array_mem(inverse), array_mem(transform), 4);

	Vector v, result, expected;
	vector_init(&v, -4, 6, 8);
	vector_init(&expected, -2, 2, 2);

	matrix_mul_tuple(&result, array_mem(inverse), &v);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void rotating_a_point_around_the_x_axis()
{
	Point result_one, result_two;
	Matrix half_quarter[4][4], full_quarter[4][4];

	Point p = {0, 1, 0};
	matrix_rotation_x(array_mem(half_quarter), M_PI_4);
	matrix_rotation_x(array_mem(full_quarter), M_PI_2);

	Point expected_one = {0, sqrtf(2)/2, sqrtf(2)/2};
	Point expected_two = {0, 0, 1};

	matrix_mul_tuple(&result_one, array_mem(half_quarter), &p);
	if (tuple_equal(&expected_one, &result_one))
		return test_failed();

	matrix_mul_tuple(&result_two, array_mem(full_quarter), &p);
	if (tuple_equal(&expected_two, &result_two))
		return test_failed();
	
	test_passed();
}

void inverse_of_an_x_rotation_rotates_in_the_opposite_direction()
{
	Point p, result, expected;
	Matrix half_quarter[4][4], inverse[4][4];

	point_init(&p, 0, 1, 0);
	point_init(&expected, 0, sqrtf(2)/2, -sqrtf(2)/2);
	matrix_rotation_x(array_mem(half_quarter), M_PI_4);
	matrix_inverse(array_mem(inverse), array_mem(half_quarter), 4);

	matrix_mul_tuple(&result, array_mem(inverse), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void rotating_a_point_around_the_y_axis()
{
	Point p, result_one, result_two, expected_one, expected_two;
	Matrix half_quarter[4][4], full_quarter[4][4];

	point_init(&p, 0, 0, 1);
	point_init(&expected_one, sqrtf(2)/2, 0, sqrtf(2)/2);
	point_init(&expected_two, 1, 0, 0);

	matrix_rotation_y(array_mem(half_quarter), M_PI_4);
	matrix_rotation_y(array_mem(full_quarter), M_PI_2);

	matrix_mul_tuple(&result_one, array_mem(half_quarter), &p);
	if (tuple_equal(&expected_one, &result_one))
		return test_failed();
	
	matrix_mul_tuple(&result_two, array_mem(full_quarter), &p);
	if (tuple_equal(&expected_two, &result_two))
		return test_failed();
	
	test_passed();
}

void rotating_a_point_around_the_z_axis()
{
	Point p, result_one, result_two, expected_one, expected_two;
	Matrix half_quarter[4][4], full_quarter[4][4];

	point_init(&p, 0, 1, 0);
	point_init(&expected_one, -sqrtf(2)/2, sqrtf(2)/2, 0);
	point_init(&expected_two, -1, 0, 0);

	matrix_rotation_z(array_mem(half_quarter), M_PI_4);
	matrix_rotation_z(array_mem(full_quarter), M_PI_2);

	matrix_mul_tuple(&result_one, array_mem(half_quarter), &p);
	if (tuple_equal(&expected_one, &result_one))
		return test_failed();
	
	matrix_mul_tuple(&result_two, array_mem(full_quarter), &p);
	if (tuple_equal(&expected_two, &result_two))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_x_in_proportion_to_y()
{
	Matrix transform[4][4];
	Point p, result, expected;

	matrix_shearing(array_mem(transform), 1, 0, 0, 0, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 5, 3, 4);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_x_in_proportion_to_z()
{
	Matrix transform[4][4];
	Point p, result, expected;

	matrix_shearing(array_mem(transform), 0, 1, 0, 0, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 6, 3, 4);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_y_in_proportion_to_x()
{
	Matrix transform[4][4];
	Point p, result, expected;

	matrix_shearing(array_mem(transform), 0, 0, 1, 0, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 5, 4);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_y_in_proportion_to_z()
{
	Matrix transform[4][4];
	Point p, result, expected;

	matrix_shearing(array_mem(transform), 0, 0, 0, 1, 0, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 7, 4);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_z_in_proportion_to_x()
{
	Matrix transform[4][4];
	Point p, result, expected;

	matrix_shearing(array_mem(transform), 0, 0, 0, 0, 1, 0);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 3, 6);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void a_shearing_transformation_moves_z_in_proportion_to_y()
{
	Matrix transform[4][4];
	Point p, result, expected;

	matrix_shearing(array_mem(transform), 0, 0, 0, 0, 0, 1);
	point_init(&p, 2, 3, 4);
	point_init(&expected, 2, 3, 7);

	matrix_mul_tuple(&result, array_mem(transform), &p);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void individual_transformations_are_applied_in_sequence()
{
	Matrix A[4][4], B[4][4], C[4][4];
	Point p, p2, p3, p4;
	Point expected1, expected2, expected3;

	point_init(&p, 1, 0, 1);
	matrix_rotation_x(array_mem(A), M_PI_2);
	matrix_scaling(array_mem(B), 5, 5, 5);
	matrix_translation(array_mem(C), 10, 5, 7);

	point_init(&expected1, 1, -1, 0);
	point_init(&expected2, 5, -5, 0);
	point_init(&expected3, 15, 0, 7);

	matrix_mul_tuple(&p2, array_mem(A), &p);
	if (tuple_equal(&expected1, &p2))
		return test_failed();
	
	matrix_mul_tuple(&p3, array_mem(B), &p2);
	if (tuple_equal(&expected2, &p3))
		return test_failed();

	matrix_mul_tuple(&p4, array_mem(C), &p3);
	if (tuple_equal(&expected3, &p4))
		return test_failed();
	
	test_passed();
}


void the_transformation_matrix_for_the_default_orientation()
{
	Point from;
	point_init(&from, 0, 0, 0);

	Point to;
	point_init(&to, 0, 0, -1);

	Vector up;
	vector_init(&up, 0, 1, 0);

	Matrix t[4][4];
	matrix_view_transformation(array_mem(t), &from, &to, &up);

	Matrix expected[4][4];
	matrix_identity(array_mem(expected), 4);

	if (matrix_equal(array_mem(expected), array_mem(t), 4))
		return test_failed();
	
	test_passed();
}


void a_view_transformation_matrix_looking_in_positive_z_direction()
{
	Point from;
	point_init(&from, 0, 0, 0);
	
	Point to;
	point_init(&to, 0, 0, 1);

	Vector up;
	vector_init(&up, 0, 1, 0);

	Matrix t[4][4];
	matrix_view_transformation(array_mem(t), &from, &to, &up);

	Matrix expected[4][4];
	matrix_scaling(array_mem(expected), -1, 1, -1);

	if (matrix_equal(array_mem(expected), array_mem(t), 4))
		return test_failed();
	
	test_passed();
}


void the_view_transformation_move_the_world()
{
	Point from;
	point_init(&from, 0, 0, 8);

	Point to;
	point_init(&to, 0, 0, 0);

	Vector up;
	vector_init(&up, 0, 1, 0);

	Matrix t[4][4];
	matrix_view_transformation(array_mem(t), &from, &to, &up);

	Matrix expected[4][4];
	matrix_translation(array_mem(expected), 0, 0, -8);

	if (matrix_equal(array_mem(expected), array_mem(t), 4))
		return test_failed();
	
	test_passed();
}


void an_arbitrary_view_transformation()
{
	Point from;
	point_init(&from, 1, 3, 2);

	Point to;
	point_init(&to, 4, -2, 8);

	Vector up;
	vector_init(&up, 1, 1, 0);

	Matrix t[4][4];
	matrix_view_transformation(array_mem(t), &from, &to, &up);

	Matrix expected[4][4] = {{-0.50709, 0.50709, 0.67612, -2.36643},
							 {0.76772,  0.60609, 0.12122, -2.82843},
							 {-0.35857, 0.59761, -0.71714, 0.00000},
							 {0.00000, 0.00000, 0.00000, 1.00000}};

	if (matrix_equal(array_mem(expected), array_mem(t), 4))
		return test_failed();
	
	test_passed()
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
	the_transformation_matrix_for_the_default_orientation();
	a_view_transformation_matrix_looking_in_positive_z_direction();
	the_view_transformation_move_the_world();
	an_arbitrary_view_transformation();
	test_results();
	return 0;
}


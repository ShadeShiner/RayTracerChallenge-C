#include <stdio.h>
#include <math.h>
#include <test_library.h>

#include "camera.h"
#include "matrix.h"
#include "ray.h"
#include "world.h"
#include "canvas.h"


void constructing_a_camera()
{
	unsigned int hsize = 160;
	unsigned int vsize = 120;
	unsigned int field_of_view = M_PI_2;

	Camera c;
	camera_init(&c, hsize, vsize, field_of_view);

	if (c.hsize != hsize)
		return test_failed();
	
	if (c.vsize != vsize)
		return test_failed();
	
	if (c.field_of_view != field_of_view)
		return test_failed();
	
	Matrix expected[4][4];
	matrix_identity(array_mem(expected), 4);

	if (matrix_equal(array_mem(expected), array_mem(c.transform), 4))
		return test_failed();
	
	test_passed();
}


void the_pixel_size_for_a_horizontal_canvas()
{
	Camera c;
	camera_init(&c, 200, 125, M_PI_2);

	if (float_equal(0.01, c.pixel_size))
		return test_failed();
	
	test_passed();
}


void the_pixel_size_for_a_vertical_canvas()
{
	Camera c;
	camera_init(&c, 125, 200, M_PI_2);

	if (float_equal(0.01, c.pixel_size))
		return test_failed();
	
	test_passed();
}


void constructing_a_ray_through_the_center_of_the_canvas()
{
	Camera c;
	camera_init(&c, 201, 101, M_PI_2);

	Ray r;
	ray_for_pixel(&r, &c, 100, 50);

	Point expected_point;
	point_init(&expected_point, 0, 0, 0);

	Vector expected_vector;
	vector_init(&expected_vector, 0, 0, -1);

	if (point_equal(&expected_point, r.origin))
		return test_failed();
	
	if (vector_equal(&expected_vector, r.direction))
		return test_failed();
	
	test_passed();
}


void constructing_a_ray_through_a_corner_of_the_canavs()
{
	Camera c;
	camera_init(&c, 201, 101, M_PI_2);

	Ray r;
	ray_for_pixel(&r, &c, 0, 0);

	Point expected_point;
	point_init(&expected_point, 0, 0, 0);

	Vector expected_direction;
	vector_init(&expected_direction, 0.66519, 0.33259, -0.66851);

	if (point_equal(&expected_point, r.origin))
		return test_failed();
	
	if (vector_equal(&expected_direction, r.direction))
		return test_failed();
	
	test_passed();
}


void constructing_a_ray_when_the_camera_is_transformed()
{
	Camera c;
	camera_init(&c, 201, 101, M_PI_2);

	Matrix translation[4][4];
	matrix_translation(array_mem(translation), 0, -2, 5);

	Matrix rotation[4][4];
	matrix_rotation_y(array_mem(rotation), M_PI_4);

	matrix_mul(array_mem(c.transform), array_mem(rotation),
			   array_mem(translation), 4);
	
	Ray r;
	ray_for_pixel(&r, &c, 100, 50);

	Point expected_point;
	point_init(&expected_point, 0, 2, -5);

	Vector expected_direction;
	vector_init(&expected_direction, sqrtf(2)/2, 0, -sqrtf(2)/2);

	if (point_equal(&expected_point, r.origin))
		return test_failed();
	
	if (vector_equal(&expected_direction, r.direction))
		return test_failed();
	
	test_passed();
}


void rendering_a_world_with_a_camera()
{
	World w;
	world_default(&w);

	Camera c;
	camera_init(&c, 11, 11, M_PI_2);

	Point from;
	point_init(&from, 0, 0, -5);

	Point to;
	point_init(&to, 0, 0, 0);

	Vector up;
	vector_init(&up, 0, 1, 0);

	matrix_view_transformation(array_mem(c.transform),
							   &from, &to, &up);
	
	Canvas image;
	canvas_render(&image, &c, &w);
	Color result = pixel_at(&image, 5, 5);

	Color expected;
	color_init(&expected, 0.38066, 0.47583, 0.2855);

	if (color_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}


int main()
{
	test_header();
	constructing_a_camera();
	the_pixel_size_for_a_horizontal_canvas();
	the_pixel_size_for_a_vertical_canvas();
	constructing_a_ray_through_the_center_of_the_canvas();
	constructing_a_ray_through_a_corner_of_the_canavs();
	constructing_a_ray_when_the_camera_is_transformed();
	rendering_a_world_with_a_camera();
	test_results();
}

#include <stdlib.h>
#include <math.h>
#include <test_library.h>
#include <material.h>
#include <tuple.h>

/* Setup */

typedef struct SetupData_
{
	Material *m;
	Point *position;
} SetupData;

SetupData* setup()
{
	SetupData *data = malloc(sizeof(SetupData));
	data->m = material_default_create();

	data->position = malloc(sizeof(Point));
	point_init(data->position, 0, 0, 0);

	return data;
}

/* Test Cases */

void the_default_material()
{
	Material m;
	Color expected;

	color_init(&expected, 1, 1, 1);
	material_default_init(&m);

	if (tuple_equal(&expected, m.color))
		return test_failed();
	
	if (float_equal(m.ambient, 0.1))
		return test_failed();
	
	if (float_equal(m.diffuse, 0.9))
		return test_failed();
	
	if (float_equal(m.specular, 0.9))
		return test_failed();
	
	if (float_equal(m.shininess, 200.0))
		return test_failed();
	
	test_passed();
}

void lighting_with_the_eye_between_the_light_and_the_surface()
{
	SetupData *data = setup();

	Vector eyev, normalv;
	PointLight light;
	Point p;
	Color c, expected;

	vector_init(&eyev, 0, 0, -1);
	vector_init(&normalv, 0, 0, -1);

	point_init(&p, 0, 0, -10);
	color_init(&c, 1, 1, 1);
	color_init(&expected, 1, 1, 1);
	point_light_init(&light, &p, &c);

	Color *result = material_lighting(data->m, &light, data->position, &eyev, &normalv);
	if (tuple_equal(&expected, result))
		return test_failed();
	
	test_passed();
}

void lighting_with_the_eye_between_light_and_surface_eye_offset_45_degrees()
{
	SetupData *data = setup();

	Vector eyev, normalv;
	PointLight light;
	Point p;
	Color c, expected;

	vector_init(&eyev, 0, sqrtf(2)/2, -sqrtf(2)/2);
	vector_init(&normalv, 0, 0, -1);

	point_init(&p, 0, 0, -10);
	color_init(&c, 1, 1, 1);
	color_init(&expected, 1, 1, 1);
	point_light_init(&light, &p, &c);

	Color *result = material_lighting(data->m, &light, data->position, &eyev, &normalv);
	if (tuple_equal(&expected, result))
		return test_failed();
	
	test_passed();
}

void lighting_with_eye_opposite_surface_light_offset_45_degrees()
{
	SetupData *data = setup();

	Vector eyev, normalv;
	PointLight light;
	Point p;
	Color c, expected;

	vector_init(&eyev, 0, 0, -1);
	vector_init(&normalv, 0, 0, -1);

	point_init(&p, 0, 10, -10);
	color_init(&c, 1, 1, 1);
	color_init(&expected, 0.7364, 0.7364, 0.7364);
	point_light_init(&light, &p, &c);

	Color *result = material_lighting(data->m, &light, data->position, &eyev, &normalv);
	if (tuple_equal(&expected, result))
		return test_failed();
	
	test_passed();
}

void lighting_with_eye_in_the_path_of_the_reflection_vector()
{
	SetupData *data = setup();

	Vector eyev, normalv;
	PointLight light;
	Point p;
	Color c, expected;

	vector_init(&eyev, 0, -sqrtf(2)/2, -sqrtf(2)/2);
	vector_init(&normalv, 0, 0, -1);

	point_init(&p, 0, 10, -10);
	color_init(&c, 1, 1, 1);
	color_init(&expected, 1.6364, 1.6364, 1.6364);
	point_light_init(&light, &p, &c);

	Color *result = material_lighting(data->m, &light, data->position, &eyev, &normalv);
	if (tuple_equal(&expected, result))
		return test_failed();
	
	test_passed();
}

void lighting_with_the_light_behind_the_surface()
{
	SetupData *data = setup();

	Vector eyev, normalv;
	PointLight light;
	Point p;
	Color c, expected;

	vector_init(&eyev, 0, 0, -1);
	vector_init(&normalv, 0, 0, -1);

	point_init(&p, 0, 0, 10);
	color_init(&c, 1, 1, 1);
	color_init(&expected, 0.1, 0.1, 0.1);
	point_light_init(&light, &p, &c);

	Color *result = material_lighting(data->m, &light, data->position, &eyev, &normalv);
	if (tuple_equal(&expected, result))
		return test_failed();
	
	test_passed();
}

int main()
{
	test_header();
	the_default_material();
	lighting_with_the_eye_between_the_light_and_the_surface();
	lighting_with_the_eye_between_light_and_surface_eye_offset_45_degrees();
	lighting_with_eye_opposite_surface_light_offset_45_degrees();
	lighting_with_eye_in_the_path_of_the_reflection_vector();
	lighting_with_the_light_behind_the_surface();
	test_results();
	return 0;
}

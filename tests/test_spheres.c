#include <stdio.h>
#include <math.h>
#include <test_library.h>
#include <sphere.h>
#include <ray.h>
#include <tuple.h>
#include <intersections.h>

void a_ray_intersects_a_sphere_at_two_points()
{
	Ray r;
	Point p;
	Vector v;
	
	point_init(&p, 0, 0, -5);
	vector_init(&v, 0, 0, 1);
	ray_init(&r, &p, &v);

	Sphere s;
	sphere_init(&s);

	IntersectGroup xs;
	intersect_group_init(&xs);

	sphere_intersect(&xs, &s, &r);

	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(4.0, intersect_group_get(&xs, 0)->t))
		return test_failed();
	
	if (float_equal(6.0, intersect_group_get(&xs, 1)->t))
		return test_failed();
	
	test_passed();
}

void a_ray_intersects_a_sphere_at_a_tangent()
{
	Ray r;
	Point p;
	Vector v;

	point_init(&p, 0, 1, -5);
	vector_init(&v, 0, 0, 1);
	ray_init(&r, &p, &v);

	Sphere s;
	sphere_init(&s);

	IntersectGroup xs;
	intersect_group_init(&xs);

	sphere_intersect(&xs, &s, &r);
	
	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(5.0, intersect_group_get(&xs, 0)->t))
		return test_failed();
	
	if (float_equal(5.0, intersect_group_get(&xs, 1)->t))
		return test_failed();
	
	test_passed();
}

void a_ray_misses_a_sphere()
{
	Ray r;
	Point p;
	Vector v;

	point_init(&p, 0, 2, -5);
	vector_init(&v, 0, 0, 1);
	ray_init(&r, &p, &v);

	Sphere s;
	sphere_init(&s);

	IntersectGroup xs;
	intersect_group_init(&xs);

	sphere_intersect(&xs, &s, &r);

	if (xs.count != 0)
		return test_failed();
	
	test_passed();
}

void a_ray_originates_inside_a_sphere()
{
	Ray r;
	Point p;
	Vector v;

	point_init(&p, 0, 0, 0);
	vector_init(&v, 0, 0, 1);
	ray_init(&r, &p, &v);

	Sphere s;
	sphere_init(&s);

	IntersectGroup xs;
	intersect_group_init(&xs);

	sphere_intersect(&xs, &s, &r);

	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(-1.0, intersect_group_get(&xs, 0)->t))
		return test_failed();
	
	if (float_equal(1.0, intersect_group_get(&xs, 1)->t))
		return test_failed();
	
	test_passed();
}

void a_sphere_is_behind_a_ray()
{
	Ray r;
	Point p;
	Vector v;

	point_init(&p, 0, 0, 5);
	vector_init(&v, 0, 0, 1);
	ray_init(&r, &p, &v);

	Sphere s;
	sphere_init(&s);

	IntersectGroup xs;
	intersect_group_init(&xs);

	sphere_intersect(&xs, &s, &r);

	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(-6.0, intersect_group_get(&xs, 0)->t))
		return test_failed();
	
	if (float_equal(-4.0, intersect_group_get(&xs, 1)->t))
		return test_failed();
	
	test_passed();
}

void intersect_sets_the_object_on_the_intersection()
{
	Ray r;
	Point p;
	Vector v;

	point_init(&p, 0, 0, -5);
	vector_init(&v, 0, 0, 1);
	ray_init(&r, &p, &v);

	IntersectGroup xs;
	intersect_group_init(&xs);

	Sphere s;
	sphere_init(&s);
	sphere_intersect(&xs, &s, &r);

	if (xs.count != 2)
		return test_failed();
	
	if (intersect_group_get(&xs, 0)->object != &s)
		return test_failed();

	if (intersect_group_get(&xs, 1)->object != &s)
		return test_failed();
	
	test_passed();
}

void a_spheres_default_transformation()
{
	Sphere s;
	Matrix identity[4][4];

	sphere_init(&s);
	matrix_identity(array_mem(identity), 4);

	if (matrix_equal(array_mem(identity), array_mem(s.transform), 4))
		return test_failed();
	
	test_passed();
}

void changing_a_spheres_transformation()
{
	Sphere s;
	Matrix t[4][4];

	sphere_init(&s);
	matrix_translation(array_mem(t), 2, 3, 4);

	sphere_set_transform(&s, array_mem(t));

	if (matrix_equal(array_mem(t), array_mem(s.transform), 4))
		return test_failed();
	
	test_passed()
}

void intersecting_a_scaled_sphere_with_a_ray()
{
	Ray r;
	Point p;
	Vector v;

	point_init(&p, 0, 0, -5);
	vector_init(&v, 0, 0, 1);
	ray_init(&r, &p, &v);

	Sphere s;
	Matrix t;

	sphere_init(&s);
	matrix_scaling(&t, 2, 2, 2);

	sphere_set_transform(&s, &t);

	IntersectGroup xs;
	intersect_group_init(&xs);
	sphere_intersect(&xs, &s, &r);
	
	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(3, intersect_group_get(&xs, 0)->t))
		return test_failed();

	if (float_equal(7, intersect_group_get(&xs, 1)->t))
		return test_failed();
	
	test_passed();
}

void the_normal_on_a_sphere_at_a_point_on_the_x_axis()
{
	Sphere s;
	Point p;
	Vector n, expected;

	sphere_init(&s);
	point_init(&p, 1, 0, 0);
	vector_init(&expected, 1, 0, 0);

	sphere_normal_at(&n, &s, &p);
	if (tuple_equal(&expected, &n))
		return test_failed();
	
	test_passed();
}

void the_normal_on_a_sphere_at_a_point_on_the_y_axis()
{
	Sphere s;
	Point p;
	Vector n, expected;

	sphere_init(&s);
	point_init(&p, 0, 1, 0);
	vector_init(&expected, 0, 1, 0);

	sphere_normal_at(&n, &s, &p);
	if (tuple_equal(&expected, &n))
		return test_failed();
	
	test_passed();
}

void the_normal_on_a_sphere_at_a_point_on_the_z_axis()
{
	Sphere s;
	Point p;
	Vector n, expected;

	sphere_init(&s);
	point_init(&p, 0, 0, 1);
	vector_init(&expected, 0, 0, 1);

	sphere_normal_at(&n, &s, &p);
	if (tuple_equal(&expected, &n))
		return test_failed();
	
	test_passed();
}

void the_normal_on_a_sphere_at_a_nonaxial_point()
{
	Sphere s;
	Point p;
	Vector n, expected;

	sphere_init(&s);
	point_init(&p, sqrtf(3)/3, sqrtf(3)/3, sqrtf(3)/3);
	vector_init(&expected, sqrtf(3)/3, sqrtf(3)/3, sqrtf(3)/3);

	sphere_normal_at(&n, &s, &p);
	if (tuple_equal(&expected, &n))
		return test_failed();
	
	test_passed();
}

void the_normal_is_a_normalized_vector()
{
	Sphere s;
	Point p;
	Vector n, result;

	sphere_init(&s);
	point_init(&p, sqrtf(3)/3, sqrtf(3)/3, sqrtf(3)/3);

	sphere_normal_at(&n, &s, &p);
	tuple_normalize(&result, &n);

	if (tuple_equal(&result, &n))
		return test_failed();
	
	test_passed();
}

void computing_the_normal_on_a_translated_sphere()
{
	Sphere s;
	Matrix transform;

	sphere_init(&s);
	matrix_translation(&transform, 0, 1, 0);
	sphere_set_transform(&s, &transform);


	Vector n, expected;
	Point p;

	point_init(&p, 0, 1.70711, -0.70711);
	vector_init(&expected, 0, 0.70711, -0.70711);
	sphere_normal_at(&n, &s, &p);

	if (tuple_equal(&expected, &n))
		return test_failed();
	
	test_passed();
}

void computing_the_normal_on_a_transformed_sphere()
{
	Sphere s;
	Matrix scaling[4][4], rotation[4][4], transform[4][4];

	sphere_init(&s);
	matrix_scaling(array_mem(scaling), 1, 0.5, 1);
	matrix_rotation_z(array_mem(rotation), M_PI / 5);
	matrix_mul(array_mem(transform), array_mem(scaling), array_mem(rotation), 4);
	sphere_set_transform(&s, array_mem(transform));

	Vector n, expected;
	Point p;

	point_init(&p, 0, sqrtf(2)/2, -sqrtf(2)/2);
	vector_init(&expected, 0, 0.97014, -0.24254);
	sphere_normal_at(&n, &s, &p);
	
	if (tuple_equal(&expected, &n))
		return test_failed();
	
	test_passed();
}

void a_sphere_has_a_default_material()
{
	Sphere s;
	Material *m, expected;

	sphere_init(&s);
	m = s.material;	
	material_default_init(&expected);

	if (material_equal(&expected, m))
		return test_failed();
	
	test_passed();
}

void a_sphere_may_be_assigned_a_material()
{
	Sphere s;
	Material m;

	sphere_init(&s);
	material_default_init(&m);
	m.ambient = 1;

	s.material = &m;
	if (material_equal(s.material, &m))
		return test_failed();
	
	test_passed();
}

int main()
{
	test_header();
	a_ray_intersects_a_sphere_at_two_points();
	a_ray_intersects_a_sphere_at_a_tangent();
	a_ray_misses_a_sphere();
	a_ray_originates_inside_a_sphere();
	a_sphere_is_behind_a_ray();
	intersect_sets_the_object_on_the_intersection();
	a_spheres_default_transformation();
	changing_a_spheres_transformation();
	intersecting_a_scaled_sphere_with_a_ray();
	the_normal_on_a_sphere_at_a_point_on_the_x_axis();
	the_normal_on_a_sphere_at_a_point_on_the_y_axis();
	the_normal_on_a_sphere_at_a_point_on_the_z_axis();
	the_normal_on_a_sphere_at_a_nonaxial_point();
	the_normal_is_a_normalized_vector();
	computing_the_normal_on_a_translated_sphere();
	computing_the_normal_on_a_transformed_sphere();
	a_sphere_has_a_default_material();
	a_sphere_may_be_assigned_a_material();
	test_results();
	return 0;
}

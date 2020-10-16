#include <stdio.h>
#include <test_library.h>
#include <sphere.h>
#include <ray.h>
#include <tuple.h>

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

int main()
{
	test_header();
	a_ray_intersects_a_sphere_at_two_points();
	a_ray_intersects_a_sphere_at_a_tangent();
	a_ray_misses_a_sphere();
	a_ray_originates_inside_a_sphere();
	a_sphere_is_behind_a_ray();
	intersect_sets_the_object_on_the_intersection();
	test_results();
	return 0;
}

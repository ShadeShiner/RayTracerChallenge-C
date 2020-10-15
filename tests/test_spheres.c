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
	Intersection xs;

	sphere_init(&s);
	sphere_intersect(&xs, &s, &r);

	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(4.0, xs.points[0]))
		return test_failed();
	
	if (float_equal(6.0, xs.points[1]))
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

	Intersection xs;
	sphere_intersect(&xs, &s, &r);
	
	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(5.0, xs.points[0]))
		return test_failed();
	
	if (float_equal(5.0, xs.points[1]))
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
	Intersection xs;

	sphere_init(&s);
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
	Intersection xs;

	sphere_init(&s);
	sphere_intersect(&xs, &s, &r);

	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(-1.0, xs.points[0]))
		return test_failed();
	
	if (float_equal(1.0, xs.points[1]))
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
	Intersection xs;

	sphere_init(&s);
	sphere_intersect(&xs, &s, &r);

	if (xs.count != 2)
		return test_failed();
	
	if (float_equal(-6.0, xs.points[0]))
		return test_failed();
	
	if (float_equal(-4.0, xs.points[1]))
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
	test_results();
	return 0;
}

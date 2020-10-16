#include <stdio.h>
#include <test_library.h>
#include <intersections.h>
#include <sphere.h>


void an_intersection_encapsulates_t_and_object()
{
	Sphere s;
	sphere_init(&s);

	Intersect i;
	intersect_init(&i, 3.5, &s);

	if (i.t != 3.5)
		return test_failed();
	
	if (i.object != &s)
		return test_failed();
	
	test_passed();
}

void aggregating_intersections()
{
	Sphere s;
	sphere_init(&s);

	Intersect i1, i2;
	intersect_init(&i1, 1, &s);
	intersect_init(&i2, 2, &s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	if (xs.count != 2)
		return test_failed();
	
	if (intersect_group_get(&xs, 0)->object != &s)
		return test_failed();
	
	if (intersect_group_get(&xs, 1)->object != &s)
		return test_failed();
	
	test_passed();
}

void the_hit_when_all_intersections_have_positive_t()
{
	Sphere s;
	sphere_init(&s);

	Intersect i1, i2;
	intersect_init(&i1, 1, &s);
	intersect_init(&i2, 2, &s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	Intersect *result = intersect_group_hit(&xs);
	if (result != &i1)
		return test_failed();
	
	test_passed();
}

void the_hit_when_some_intersections_have_negative_t()
{
	Sphere s;
	sphere_init(&s);

	Intersect i1, i2;
	intersect_init(&i1, -1, &s);
	intersect_init(&i2, 1, &s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	Intersect *result = intersect_group_hit(&xs);
	if (result != &i2)
		return test_failed();
	
	test_passed();
}

void the_hit_when_all_intersection_have_negative_t()
{
	Sphere s;
	sphere_init(&s);

	Intersect i1, i2;
	intersect_init(&i1, -2, &s);
	intersect_init(&i2, -1, &s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	Intersect *result = intersect_group_hit(&xs);
	if (result != NULL)
		return test_failed();
	
	test_passed();
}

void the_hit_is_always_the_lowest_nonnegative_intersection()
{
	Sphere s;
	sphere_init(&s);

	Intersect i1, i2, i3, i4;
	intersect_init(&i1, 5, &s);
	intersect_init(&i2, 7, &s);
	intersect_init(&i3, -3, &s);
	intersect_init(&i4, 2, &s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 4, &i1, &i2, &i3, &i4);

	Intersect *result = intersect_group_hit(&xs);
	if (result != &i4)
		return test_failed();
	
	test_passed();
}

int main()
{
	test_header();
	an_intersection_encapsulates_t_and_object();
	aggregating_intersections();
	the_hit_when_all_intersections_have_positive_t();
	the_hit_when_some_intersections_have_negative_t();
	the_hit_when_all_intersection_have_negative_t();
	the_hit_is_always_the_lowest_nonnegative_intersection();
	test_results();
	return 0;
}


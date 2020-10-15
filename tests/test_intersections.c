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

	Intersections xs;
	intersections_init(&xs);
	intersections(&xs, &i1, &i2);

	if (xs.count != 2)
		return test_failed();
	
	if (intersections_get(&xs, 0)->object != &s)
		return test_failed();
	
	if (intersections_get(&xs, 1)->object != &s)
		return test_failed();
	
	test_passed();
}

int main()
{
	test_header();
	an_intersection_encapsulates_t_and_object();
	aggregating_intersections();
	test_results();
	return 0;
}


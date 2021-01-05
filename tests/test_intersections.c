#include <stdio.h>
#include <test_library.h>
#include <intersections.h>
#include <shape.h>
#include <sphere.h>


void an_intersection_encapsulates_t_and_object()
{
	Shape *s = sphere_create();

	Intersect i;
	intersect_init(&i, 3.5, s);

	if (i.t != 3.5)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	if (i.object != s)
	{
		s->destroy(&s);
		return test_failed();
	}

	s->destroy(&s);
	test_passed();
}

void aggregating_intersections()
{
	Shape *s = sphere_create();

	Intersect i1, i2;
	intersect_init(&i1, 1, s);
	intersect_init(&i2, 2, s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	if (xs.count != 2)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	if (intersect_group_get(&xs, 0)->object != s)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	if (intersect_group_get(&xs, 1)->object != s)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}

void the_hit_when_all_intersections_have_positive_t()
{
	Shape *s = sphere_create();

	Intersect i1, i2;
	intersect_init(&i1, 1, s);
	intersect_init(&i2, 2, s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	Intersect *result = intersect_group_hit(&xs);
	if (result != &i1)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}

void the_hit_when_some_intersections_have_negative_t()
{
	Shape *s = sphere_create();

	Intersect i1, i2;
	intersect_init(&i1, -1, s);
	intersect_init(&i2, 1, s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	Intersect *result = intersect_group_hit(&xs);
	if (result != &i2)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}

void the_hit_when_all_intersection_have_negative_t()
{
	Shape *s = sphere_create();

	Intersect i1, i2;
	intersect_init(&i1, -2, s);
	intersect_init(&i2, -1, s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 2, &i1, &i2);

	Intersect *result = intersect_group_hit(&xs);
	if (result != NULL)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}

void the_hit_is_always_the_lowest_nonnegative_intersection()
{
	Shape *s = sphere_create();

	Intersect i1, i2, i3, i4;
	intersect_init(&i1, 5, s);
	intersect_init(&i2, 7, s);
	intersect_init(&i3, -3, s);
	intersect_init(&i4, 2, s);

	IntersectGroup xs;
	intersect_group_init(&xs);
	intersect_group_add(&xs, 4, &i1, &i2, &i3, &i4);

	Intersect *result = intersect_group_hit(&xs);
	if (result != &i4)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}


void precomputing_the_state_of_an_intersection()
{
	Point p;
	point_init(&p, 0, 0, -5);

	Vector v;
	vector_init(&v, 0, 0, 1);

	Ray r;
	ray_init(&r, &p, &v);

	Shape *s = sphere_create();

	Intersect i;
	intersect_init(&i, 4, s);

	PreComputed *comps = precomputed_create(&i, &r);

	if (float_equal(comps->t, i.t))
	{
		s->destroy(&s);
		return test_failed();
	}
	
	if (s->equal(comps->object, i.object))
	{
		s->destroy(&s);
		return test_failed();
	}
	
	Point p_result;
	point_init(&p_result, 0, 0, -1);
	if (point_equal(comps->point, &p_result))
	{
		s->destroy(&s);
		return test_failed();
	}
	
	Vector eye_result;
	vector_init(&eye_result, 0, 0, -1);
	if (vector_equal(comps->eyev, &eye_result))
	{
		s->destroy(&s);
		return test_failed();
	}
	
	Vector normal_result;
	vector_init(&normal_result, 0, 0, -1);
	if (vector_equal(comps->normalv, &normal_result))
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}


void the_hit_when_an_intersection_occurs_on_the_outside()
{
	Point p;
	point_init(&p, 0, 0, -5);

	Vector v;
	vector_init(&v, 0, 0, 1);

	Ray r;
	ray_init(&r, &p, &v);

	Shape *s = sphere_create();

	Intersect i;
	intersect_init(&i, 4, s);

	PreComputed *comps = precomputed_create(&i, &r);
	if (comps->inside != 0)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}


void the_hit_when_an_intersection_occurs_on_the_inside()
{
	Point p;
	point_init(&p, 0, 0, 0);

	Vector v;
	vector_init(&v, 0, 0, 1);

	Ray r;
	ray_init(&r, &p, &v);

	Shape *s = sphere_create();

	Intersect i;
	intersect_init(&i, 1, s);

	PreComputed *comps = precomputed_create(&i, &r);

	Point point_result;
	point_init(&point_result, 0, 0, 1);
	if (point_equal(comps->point, &point_result))
	{
		s->destroy(&s);
		return test_failed();
	}

	Vector eye_result;
	vector_init(&eye_result, 0, 0, -1);
	if (vector_equal(comps->eyev, &eye_result))
	{
		s->destroy(&s);
		return test_failed();
	}
	
	if (comps->inside == 0)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	Vector normal_result;
	vector_init(&normal_result, 0, 0, -1);
	if (vector_equal(comps->normalv, &normal_result))
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
	test_passed();
}


void the_hit_should_offset_the_point()
{
	Point p;
	point_init(&p, 0, 0, -5);

	Vector v;
	vector_init(&v, 0, 0, 1);

	Ray r;
	ray_init(&r, &p, &v);

	Shape *s = sphere_create();

	Matrix transform[4][4];
	matrix_translation(array_mem(transform), 0, 0, 1);

	s->set_transform(s, array_mem(transform));

	Intersect i;
	intersect_init(&i, 5, s);

	PreComputed *comps = precomputed_create(&i, &r);
	if (comps->over_point->z >= -EPSILON/2)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	if (comps->point->z <= comps->over_point->z)
	{
		s->destroy(&s);
		return test_failed();
	}
	
	s->destroy(&s);
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
	precomputing_the_state_of_an_intersection();
	the_hit_when_an_intersection_occurs_on_the_outside();
	the_hit_when_an_intersection_occurs_on_the_inside();
	the_hit_should_offset_the_point();
	test_results();
	return 0;
}


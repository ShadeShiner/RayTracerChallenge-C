#include <test_library.h>
#include <tuple.h>
#include <ray.h>
#include <matrix.h>


void creating_and_querying_a_ray()
{
	Point origin;
	Vector direction;
	Ray r;

	point_init(&origin, 1.0f, 2.0f, 3.0f);
	vector_init(&direction, 4.0f, 5.0f, 6.0f);
	ray_init(&r, &origin, &direction);

	if (point_equal(r.origin, &origin))
		return test_failed();
	
	if (vector_equal(r.direction, &direction))
		return test_failed();
	
	test_passed();
}

void computing_a_point_from_a_distance()
{
	Point p;
	Vector v;
	Ray r;

	point_init(&p, 2.0f, 3.0f, 4.0f);
	vector_init(&v, 1.0, 0.0f, 0.0f);
	ray_init(&r, &p, &v);

	Point result;
	Point expected;

	point_init(&expected, 2.0f, 3.0f, 4.0f);
	ray_position(&result, &r, 0.0f);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	point_init(&expected, 3.0f, 3.0f, 4.0f);
	ray_position(&result, &r, 1.0f);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	point_init(&expected, 1.0f, 3.0f, 4.0f);
	ray_position(&result, &r, -1.0f);
	if (tuple_equal(&expected, &result))
		return test_failed();
	
	test_passed();
}

void translating_a_ray()
{
	Ray r, r2;
	Point p, p2, expected_point;
	Vector v, v2, expected_vector;

	point_init(&p, 1, 2, 3);
	vector_init(&v, 0, 1, 0);
	ray_init(&r, &p, &v);

	point_init(&expected_point, 4, 6, 8);
	vector_init(&expected_vector, 0, 1, 0);

	Matrix m;
	matrix_translation(&m, 3, 4, 5);

	ray_init(&r2, &p2, &v2);
	ray_transform(&r2, &r, &m);

	if (tuple_equal(&expected_point, r2.origin))
		return test_failed();
	
	if (tuple_equal(&expected_vector, r2.direction))
		return test_failed();
	
	test_passed();
}

int main()
{
	test_header();
	creating_and_querying_a_ray();
	computing_a_point_from_a_distance();
	translating_a_ray();
	test_results();
	return 0;
}


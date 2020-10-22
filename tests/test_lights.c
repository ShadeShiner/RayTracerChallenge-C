#include <test_library.h>
#include <tuple.h>
#include <lights.h>


void a_point_light_has_a_position_and_intensity()
{
	PointLight light;
	Point position;
	Color intensity;

	color_init(&intensity, 1, 1, 1);
	point_init(&position, 0, 0, 0);
	point_light_init(&light, &position, &intensity);

	if (tuple_equal(light.position, &position))
		return test_failed();
	
	if (tuple_equal(light.intensity, &intensity))
		return test_failed();
	
	test_passed();
}

int main()
{
	test_header();
	a_point_light_has_a_position_and_intensity();
	test_results();
	return 0;
}


#include <lights.h>
#include <tuple.h>


void point_light_init(PointLight *point_light, Point *position, Color *intensity)
{
	point_light->position = position;
	point_light->intensity = intensity;
}


int point_light_equal(PointLight *pl1, PointLight *pl2)
{
	int result = point_equal(pl1->position, pl2->position);
	if (result)
		return result;
	
	return color_equal(pl1->intensity, pl2->intensity);
}

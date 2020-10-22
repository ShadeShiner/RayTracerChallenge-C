#include <lights.h>


void point_light_init(PointLight *point_light, Point *position, Color *intensity)
{
	point_light->position = position;
	point_light->intensity = intensity;
}


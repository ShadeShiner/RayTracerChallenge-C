#ifndef LIGHTS_H
#define LIGHTS_H

#include <tuple.h>


typedef struct PointLight_
{
	Point *position;
	Color *intensity;
} PointLight;


void point_light_init(PointLight *point_light, Point *position, Color *intensity);

int point_light_equal(PointLight *pl1, PointLight *pl2);

#endif

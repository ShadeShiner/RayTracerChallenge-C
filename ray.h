#ifndef RAY_H
#define RAY_H

#include "tuple.h"

typedef struct Ray_
{
	Point *origin;
	Vector *direction;
} Ray;

void ray_init(Ray *ray, Point *origin, Vector *direction);

void ray_position(Point *out, Ray *ray, float time);

#endif

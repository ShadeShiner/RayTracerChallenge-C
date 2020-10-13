#include "tuple.h"
#include "ray.h"

void ray_init(Ray *ray, Point *origin, Vector *direction)
{
	ray->origin = origin;
	ray->direction = direction;
}

void ray_position(Point *out, Ray *ray, float time)
{
	tuple_mul_scalar(out, ray->direction, time);
	tuple_add(out, out, ray->origin);
}


#include <tuple.h>
#include <ray.h>
#include <matrix.h>

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

void ray_transform(Ray *out, Ray *in, Matrix *m)
{
	matrix_mul_tuple(out->origin, m, in->origin);
	matrix_mul_tuple(out->direction, m, in->direction);
}


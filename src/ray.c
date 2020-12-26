#include <stdlib.h>

#include <tuple.h>
#include <ray.h>
#include <matrix.h>
#include <camera.h>


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

void ray_for_pixel(Ray *out, Camera *c, unsigned int x, unsigned int y)
{
	/* the offset from the edge of the canvas to the pixel's center */
	float xoffset = (x + 0.5) * c->pixel_size;
	float yoffset = (y + 0.5) * c->pixel_size;

	/* the untransformed coordinate of the pixel in world space */
	/* (remember that the camera looks toward -z, so +x is to the *left*.) */
	float world_x = c->half_width - xoffset;
	float world_y = c->half_height - yoffset;

	/* using the camera matrix, transform the canvas point and the origin,
	and then compute the ray's direction vector.
	(remember that the canvas is at z=-1)*/
	Matrix camera_inverse[4][4];
	matrix_inverse(array_mem(camera_inverse), array_mem(c->transform), 4);

	Point world_point;
	point_init(&world_point, world_x, world_y, -1);
	Point pixel;
	/* World point -> Camera point */
	matrix_mul_tuple(&pixel, array_mem(camera_inverse), &world_point);

	Point origin_point;
	point_init(&origin_point, 0, 0, 0);

	Point *origin = malloc(sizeof(Point));
	matrix_mul_tuple(origin, array_mem(camera_inverse), &origin_point);

	Vector direction;
	vector_sub(&direction, &pixel, origin);
	Vector *direction_normalized = malloc(sizeof(Vector));
	vector_normalize(direction_normalized, &direction);

	out->origin = origin;
	out->direction = direction_normalized;
}


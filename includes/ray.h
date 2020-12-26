#ifndef RAY_H
#define RAY_H

#include <tuple.h>
#include <matrix.h>


/* Forward Declaration */
typedef struct Camera_ Camera;

/* Structures */
typedef struct Ray_
{
	Point *origin;
	Vector *direction;
} Ray;

void ray_init(Ray *ray, Point *origin, Vector *direction);

void ray_position(Point *out, Ray *ray, float time);

void ray_transform(Ray *out, Ray *in, Matrix *m);

void ray_for_pixel(Ray *out, Camera *c, unsigned int x, unsigned int y);

#endif

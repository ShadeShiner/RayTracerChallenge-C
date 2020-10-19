#ifndef SPHERE_H
#define SPHERE_H

#include <tuple.h>
#include <ray.h>
#include <matrix.h>
#include <intersections.h>

typedef struct Sphere_
{
	unsigned int ID;
	Matrix *transform;
} Sphere;


int sphere_init(Sphere *sphere);

void sphere_set_transform(Sphere *sphere, Matrix *transform);

void sphere_intersect(IntersectGroup *intersect_group, Sphere *sphere, Ray *world_ray);

#endif

#ifndef SPHERE_H
#define SPHERE_H

#include <tuple.h>
#include <ray.h>
#include <intersections.h>

typedef struct Sphere_
{
	unsigned int ID;
} Sphere;


int sphere_init(Sphere *sphere);

void sphere_intersect(IntersectGroup *intersect_group, Sphere *sphere, Ray *ray);

#endif

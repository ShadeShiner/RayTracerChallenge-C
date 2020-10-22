#ifndef SPHERE_H
#define SPHERE_H

#include <tuple.h>
#include <ray.h>
#include <matrix.h>
#include <material.h>
#include <intersections.h>

typedef struct Sphere_
{
	unsigned int ID;
	Matrix *transform;
	Material *material;
} Sphere;


int sphere_init(Sphere *sphere);

void sphere_set_transform(Sphere *sphere, Matrix *transform);

void sphere_intersect(IntersectGroup *intersect_group, Sphere *sphere, Ray *world_ray);

void sphere_normal_at(Vector *world_normal, Sphere *sphere, Point *world_point);

#endif

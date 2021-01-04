#ifndef SPHERE_H
#define SPHERE_H

#include <tuple.h>
#include <shape.h>
#include <ray.h>
#include <matrix.h>
#include <material.h>
#include <intersections.h>


typedef struct Sphere_
{
	Shape *base;
} Sphere;


/* Constructors */
unsigned int sphere_init(Sphere *sphere);
Shape* sphere_create();

/* Destructors */
void sphere_release(Shape *shape);
void sphere_destroy(Shape *shape);

/* Functions */
void sphere_intersect(Shape *sphere, IntersectGroup *intersect_group, Ray *local_ray);
void sphere_normal_at(Vector *world_normal, Sphere *sphere, Point *world_point);

#endif

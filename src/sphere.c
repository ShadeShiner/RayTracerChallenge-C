#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sphere.h>
#include <shape.h>
#include <tuple.h>
#include <ray.h>
#include <matrix.h>
#include <material.h>
#include <intersections.h>


/* Constructors */
unsigned int sphere_init(Sphere *sphere)
{
	/* Create the base and have the base point to the child */
	sphere->base = malloc(sizeof(Shape));
	unsigned int result = shape_init(sphere->base);
	sphere->base->derived = sphere;

	/* Function Pointers */
	sphere->base->release = sphere_release;
	sphere->base->destroy = sphere_destroy;
	sphere->base->local_intersect = sphere_intersect;

	return result;
}


Shape* sphere_create()
{
	Sphere *s = malloc(sizeof(Sphere));
	sphere_init(s);
	return s->base;
}


/* Destructors */
void sphere_release(Shape **shape)
{
	// Call the base (super) object's release function
	shape_release(shape);
}


void sphere_destroy(Shape **shape)
{
	// Retrieve the derived Sphere object
	Sphere *sphere = (Sphere *)((*shape)->derived);

	// Call the base (super) object's destroy fucntion
	shape_destroy(shape);

	// Finish the subclass after super is destroyed
	free(sphere);
}


/* Functions */
void sphere_intersect(Shape *self, IntersectGroup *intersect_group, Ray *local_ray)
{
	/*
	The vector from the sphere's center, to the ray origin
	Remember: the sphere is centered at the world origin
	*/
	Point origin;
	point_init(&origin, 0, 0, 0);

	Vector sphere_to_ray;
	tuple_sub(&sphere_to_ray, local_ray->origin, &origin);

	float a = tuple_dot(local_ray->direction, local_ray->direction);
	float b = 2 * tuple_dot(local_ray->direction, &sphere_to_ray);
	float c = tuple_dot(&sphere_to_ray, &sphere_to_ray) - 1;
	float discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return;
	
	float t1 = (-b - sqrtf(discriminant)) / (2 * a);
	float t2 = (-b + sqrtf(discriminant)) / (2 * a);

	Intersect *i1 = malloc(sizeof(Intersect));
	Intersect *i2 = malloc(sizeof(Intersect));
	intersect_init(i1, t1, self);
	intersect_init(i2, t2, self);
	intersect_group_add(intersect_group, 2, i1, i2);
}


void sphere_normal_at(Vector *world_normal, Sphere *sphere, Point *world_point)
{
	/* world -> object */
	Point object_point;
	Matrix inverse[4][4], transposed[4][4];

	matrix_inverse(array_mem(inverse), array_mem(sphere->base->transform), 4);
	matrix_mul_tuple(&object_point, array_mem(inverse), world_point);

	/* calculate normal at object space coordinate */
	Point origin;
	point_init(&origin, 0, 0, 0);

	Vector object_normal;
	tuple_sub(&object_normal, &object_point, &origin);

	/* object -> world */
	Vector object_to_world;
	matrix_transpose(array_mem(transposed), array_mem(inverse), 4);
	matrix_mul_tuple(&object_to_world, array_mem(transposed), &object_normal);
	object_to_world.w = 0;
	tuple_normalize(world_normal, &object_to_world);
}

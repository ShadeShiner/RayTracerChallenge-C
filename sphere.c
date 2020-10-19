#include <stdlib.h>
#include <math.h>
#include <sphere.h>
#include <tuple.h>
#include <ray.h>
#include <matrix.h>
#include <intersections.h>


static unsigned int ID = 0;

int sphere_init(Sphere *sphere)
{
	sphere->ID = ID++;
	sphere->transform = malloc(sizeof(Matrix));
	matrix_identity(sphere->transform);
	return sphere->ID;
}

void sphere_set_transform(Sphere *sphere, Matrix *transform)
{
	sphere->transform = transform;
}

void sphere_intersect(IntersectGroup *intersect_group, Sphere *sphere, Ray *world_ray)
{
	Matrix world_to_local;
	matrix_inverse(&world_to_local, sphere->transform);

	Ray object_ray;
	Point p;
	Vector v;

	ray_init(&object_ray, &p, &v);
	ray_transform(&object_ray, world_ray, &world_to_local);

	/*
	The vector from the sphere's center, to the ray origin
	Remember: the sphere is centered at the world origin
	*/
	Point origin;
	point_init(&origin, 0, 0, 0);

	Vector sphere_to_ray;
	tuple_sub(&sphere_to_ray, object_ray.origin, &origin);

	float a = tuple_dot(object_ray.direction, object_ray.direction);
	float b = 2 * tuple_dot(object_ray.direction, &sphere_to_ray);
	float c = tuple_dot(&sphere_to_ray, &sphere_to_ray) - 1;
	float discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return;
	
	float t1 = (-b - sqrtf(discriminant)) / (2 * a);
	float t2 = (-b + sqrtf(discriminant)) / (2 * a);

	Intersect *i1 = malloc(sizeof(Intersect));
	Intersect *i2 = malloc(sizeof(Intersect));
	intersect_init(i1, t1, sphere);
	intersect_init(i2, t2, sphere);
	intersect_group_add(intersect_group, 2, i1, i2);
}


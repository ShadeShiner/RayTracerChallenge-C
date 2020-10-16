#include <stdlib.h>
#include <math.h>
#include <sphere.h>
#include <tuple.h>
#include <ray.h>
#include <intersections.h>


static unsigned int ID = 0;

int sphere_init(Sphere *sphere)
{
	sphere->ID = ID++;
	return sphere->ID;
}

void sphere_intersect(IntersectGroup *intersect_group, Sphere *sphere, Ray *ray)
{
	/*
	The vector from the sphere's center, to the ray origin
	Remember: the sphere is centered at the world origin
	*/
	Point origin;
	point_init(&origin, 0, 0, 0);

	Vector sphere_to_ray;
	tuple_sub(&sphere_to_ray, ray->origin, &origin);

	float a = tuple_dot(ray->direction, ray->direction);
	float b = 2 * tuple_dot(ray->direction, &sphere_to_ray);
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
	intersect_group_add(intersect_group, i1, i2);
}


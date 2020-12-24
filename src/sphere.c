#include <stdlib.h>
#include <math.h>

#include <sphere.h>
#include <tuple.h>
#include <ray.h>
#include <matrix.h>
#include <material.h>
#include <intersections.h>


static unsigned int ID = 0;

int sphere_init(Sphere *sphere)
{
	sphere->ID = ID++;
	matrix_identity(array_mem(sphere->transform), 4);
	sphere->material = material_default_create();
	return sphere->ID;
}

Sphere* sphere_create()
{
	Sphere *s = malloc(sizeof(Sphere));
	sphere_init(s);
	return s;
}

int sphere_equal(const void *o1, const void *o2)
{
	Sphere *s1 = (Sphere *)o1;
	Sphere *s2 = (Sphere *)o2;

	int result = matrix_equal(array_mem(s1->transform), array_mem(s2->transform), 4);
	if (result)
		return result;
	
	return material_equal(s1->material, s2->material);
}

void sphere_set_transform(Sphere *sphere, Matrix *transform)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			sphere->transform[i][j] = matrix_get(transform, i, j, 4);
		}
	}
}

void sphere_intersect(IntersectGroup *intersect_group, Sphere *sphere, Ray *world_ray)
{
	Matrix world_to_local[4][4];
	matrix_inverse(array_mem(world_to_local), array_mem(sphere->transform), 4);

	Ray object_ray;
	Point p;
	Vector v;

	ray_init(&object_ray, &p, &v);
	ray_transform(&object_ray, world_ray, array_mem(world_to_local));

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

void sphere_normal_at(Vector *world_normal, Sphere *sphere, Point *world_point)
{
	/* world -> object */
	Point object_point;
	Matrix inverse[4][4], transposed[4][4];

	matrix_inverse(array_mem(inverse), array_mem(sphere->transform), 4);
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


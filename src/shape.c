#include <stdlib.h>
#include <string.h>

#include "shape.h"
#include "matrix.h"
#include "material.h"
#include "ray.h"


static unsigned int SHAPE_ID = 0;


/* Constructors */
unsigned int shape_init(Shape *shape)
{
    shape->derived = shape;
    shape->ID = SHAPE_ID++;

    matrix_identity(array_mem(shape->transform), 4);
    shape->material = material_default_create();


    /* Function Pointers */
    shape->release = shape_release;
    shape->destroy = shape_destroy;

    shape->set_transform = shape_set_transform;
    shape->equal = shape_equal;
    shape->world_to_local = convert_world_to_local_space;

    shape->intersect = shape_intersect;
    shape->local_intersect = 0;

    return shape->ID;
}


Shape* shape_create()
{
    Shape *shape = malloc(sizeof(Shape));
    shape_init(shape);
    return shape;
}


/* Destructors */
void shape_release(Shape *shape)
{
    material_destroy(shape->material);
    memset(shape, 0, sizeof(Shape));
}


void shape_destroy(Shape *shape)
{
    shape_release(shape);
    free(shape);
    shape = 0;
}


/* Functions */
int shape_equal(Shape *s1, Shape *s2)
{
    int result = matrix_equal(array_mem(s1->transform), array_mem(s2->transform), 4);
	if (result)
		return result;
	
	return material_equal(s1->material, s2->material);
}


void shape_set_transform(Shape *shape, Matrix *transform)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            shape->transform[i][j] = matrix_get(transform, i, j, 4);
        }
    }
}


void convert_world_to_local_space(Shape *shape, Ray *local, Ray *world)
{
    Matrix world_to_local[4][4];
	matrix_inverse(array_mem(world_to_local), array_mem(shape->transform), 4);
	ray_transform(local, world, array_mem(world_to_local));
}


int shape_intersect(Shape *shape, IntersectGroup *intersections, Ray *world_ray)
{
    /* Convert a ray in world space to local space first */
    Ray local_ray;
    shape->world_to_local(shape, &local_ray, world_ray);

    /* Checks to see if the shape object has 
    implemented a local ray intersection function */
    if (!shape->local_intersect) return -1;

    /* Call the function to see of the now converted
    local space ray intersect with the shape object */
    shape->local_intersect(shape, intersections, &local_ray);
    return 0;
}

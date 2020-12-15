#include <test_library.h>
#include "world.h"
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "lights.h"
#include "sphere.h"


void creating_a_world()
{
    World w;
    world_init(&w);

    if (list_size(&world_objects(&w)))
        return test_failed();
    
    if (world_light(&w))
        return test_failed();
    
    test_passed();
}


void the_default_world()
{
    Point p;
    point_init(&p, -10, 10, -10);

    Color c;
    color_init(&c, 1, 1, 1);

    PointLight expected = { &p, &c };

    Sphere s1;
    sphere_init(&s1);
    color_init(s1.material->color, 0.8, 1.0, 0.6);
    s1.material->diffuse = 0.7;
    s1.material->specular = 0.2;

    Sphere s2;
    sphere_init(&s2);
    matrix_scaling(s2.transform, 0.5, 0.5, 0.5);

    World w;
    world_default(&w);

    int result = point_light_equal(&expected, world_light(&w));
    if (result)
        return test_failed();
    
    result = world_has_object(&w, (void *)&s1);
    if (result != 0)
        return test_failed();
    
    result = world_has_object(&w, (void *)&s2);
    if (result != 0)
        return test_failed();
    
    test_passed();
}


void intersect_a_world_with_a_ray()
{
    World w;
    world_default(&w);

    Point p;
    point_init(&p, 0, 0, -5);

    Vector v;
    vector_init(&v, 0, 0, 1);

    Ray r;
    ray_init(&r, &p, &v);

    IntersectGroup *xs = world_intersect(&w, &r);
    if (xs->count != 4)
        return test_failed();
    
    if (float_equal(intersect_group_get(xs, 0)->t, 4))
        return test_failed();
    
    if (float_equal(intersect_group_get(xs, 1)->t, 4.5))
        return test_failed();

    if (float_equal(intersect_group_get(xs, 2)->t, 5.5))
        return test_failed();

    if (float_equal(intersect_group_get(xs, 3)->t, 6))
        return test_failed();
    
    test_passed();
}


int main()
{
    test_header();
    creating_a_world();
    the_default_world();
    intersect_a_world_with_a_ray();
    test_results();
    return 0;
}
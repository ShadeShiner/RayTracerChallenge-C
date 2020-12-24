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
    matrix_scaling(array_mem(s2.transform), 0.5, 0.5, 0.5);

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


void shading_an_intersection()
{
    World w;
    world_default(&w);

    Point p;
    point_init(&p, 0, 0, -5);

    Vector v;
    vector_init(&v, 0, 0, 1);

    Ray r;
    ray_init(&r, &p, &v);

    Sphere *shape = world_get_object(&w, 0);

    Intersect i;
    intersect_init(&i, 4, shape);

    PreComputed *comps = precomputed_create(&i, &r);

    Color *c = world_shade_hit(&w, comps);
    Color expected_color;
    color_init(&expected_color, 0.38066, 0.47583, 0.2855);

    if (tuple_equal(&expected_color, c))
        return test_failed();
    
    test_passed();
}


void shading_an_intersection_from_the_inside()
{
    World w;
    world_default(&w);

    Point lp;
    point_init(&lp, 0, 0.25, 0);

    Color lc;
    color_init(&lc, 1, 1, 1);

    point_light_init(w.light, &lp, &lc);

    Point p;
    point_init(&p, 0, 0.25, 0);

    Vector v;
    vector_init(&v, 0, 0, 1);

    Ray r;
    ray_init(&r, &p, &v);

    Sphere *shape = world_get_object(&w, 1);

    Intersect i;
    intersect_init(&i, 0.5, shape);

    PreComputed *comps = precomputed_create(&i, &r);
    Color *result = world_shade_hit(&w, comps);
    Color expected;
    color_init(&expected, 0.90498, 0.90498, 0.90498);

    if (color_equal(&expected, result))
        return test_failed();
    
    test_passed();
}


void the_color_when_a_ray_misses()
{
    World w;
    world_default(&w);

    Point p;
    point_init(&p, 0, 0, -5);

    Vector v;
    vector_init(&v, 0, 1, 0);

    Ray r;
    ray_init(&r, &p, &v);

    Color *result = world_color_at(&w, &r);
    Color expected;
    color_init(&expected, 0, 0, 0);

    if (color_equal(&expected, result))
        return test_failed();
    
    test_passed();
}


void the_color_when_a_ray_hits()
{
    World w;
    world_default(&w);

    Point p;
    point_init(&p, 0, 0, -5);

    Vector v;
    vector_init(&v, 0, 0, 1);

    Ray r;
    ray_init(&r, &p, &v);

    Color *result = world_color_at(&w, &r);
    Color expected;
    color_init(&expected, 0.38066, 0.47583, 0.2855);

    if (color_equal(&expected, result))
        return test_failed();
    
    test_passed();
}


void the_color_with_an_intersection_behind_the_ray()
{
    World w;
    world_default(&w);

    Sphere *outer = world_get_object(&w, 0);
    outer->material->ambient = 1;

    Sphere *inner = world_get_object(&w, 1);
    inner->material->ambient = 1;

    Point p;
    point_init(&p, 0, 0, 0.75);

    Vector v;
    vector_init(&v, 0, 0, -1);

    Ray r;
    ray_init(&r, &p, &v);

    Color *result = world_color_at(&w, &r);
    if (color_equal(inner->material->color, result))
        return test_failed();
    
    test_passed();
}


int main()
{
    test_header();
    creating_a_world();
    the_default_world();
    intersect_a_world_with_a_ray();
    shading_an_intersection();
    shading_an_intersection_from_the_inside();
    the_color_when_a_ray_misses();
    the_color_when_a_ray_hits();
    the_color_with_an_intersection_behind_the_ray();
    test_results();
    return 0;
}
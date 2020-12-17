#include <stdlib.h>
#include "world.h"
#include "lights.h"
#include "tuple.h"
#include "matrix.h"
#include "intersections.h"
#include "ray.h"
#include "sphere.h"
#include "material.h"


/* List Interface */
void list_init(List *list,
               int (*compare)(const void *data1, const void *data2))
{
    list->head = 0;
    list->tail = 0;
    list->size = 0;

    list->compare = compare;
}

int list_add(List *list, ListNode *node, void *data)
{
    ListNode *new_node = malloc(sizeof(ListNode));
    if (!new_node)
        return -1;
    new_node->data = data;

    if (node)
    {
        new_node->next = node->next;
        node->next = new_node;

        if (!new_node->next)
            list->tail = new_node;
    }
    else
    {
        new_node->next = list->head;
        list->head = new_node;

        if (!list->head->next)
            list->tail = list->head;
    }
    
    list->size++;

    return 0;
}

int list_contains(List *list, const void *data)
{
    ListNode *node;

    for (node = list->head; node; node = node->next)
    {
        if (list->compare(node->data, data) == 0)
            return 0;
    }
    
    return -1;
}

/* World Interface */
void world_init(World *world)
{
    list_init(&world->objects, sphere_equal);
    world->light = 0;
}

int world_default(World *world)
{
    world_init(world);

    Sphere *s2 = sphere_create();
    matrix_scaling(s2->transform, 0.5, 0.5, 0.5);
    if (world_add_object(world, (void *)s2) != 0)
        return -1;

    Sphere *s1 = sphere_create();
    color_init(s1->material->color, 0.8, 1.0, 0.6);
    s1->material->diffuse = 0.7;
    s1->material->specular = 0.2;
    if (world_add_object(world, (void *)s1) != 0)
        return -1;

    world->light = (PointLight *)malloc(sizeof(PointLight));
    Point *p = (Point *)malloc(sizeof(Point));
    point_init(p, -10, 10, -10);
    Color *c = (Color *)malloc(sizeof(Color));
    color_init(c, 1, 1, 1);
    point_light_init(world->light, p, c);

    return 0;
}

int world_add_object(World * world, void *object)
{
    return list_add(&world->objects, 0, object);
}

Sphere*
world_get_object(World *world, unsigned int index)
{
    ListNode *element;
    unsigned i;
    for (element = world->objects.head, i = 0;
         i < index;
         element = element->next, ++i);
    
    return (Sphere *)element->data;
}

int world_has_object(World *world, const void *object)
{
    return list_contains(&world->objects, object);
}

IntersectGroup* world_intersect(World *w, Ray *r)
{
    IntersectGroup *xs = malloc(sizeof(IntersectGroup));

    ListNode *element;
    for (element = list_head(&w->objects); element; element = element->next)
    {
        Sphere *sphere = (Sphere *)list_data(element);
        sphere_intersect(xs, sphere, r);
    }

    return xs;
}

Color*
world_shade_hit(World *w, PreComputed *comps)
{
    return material_lighting(comps->object->material,
                             w->light,
                             comps->point, comps->eyev, comps->normalv);
}

Color*
world_color_at(World *w, Ray *r)
{
    IntersectGroup *xs = world_intersect(w, r);
    Intersect *hit = intersect_group_hit(xs);

    if (hit == NULL)
    {
        Color *black = malloc(sizeof(Color));
        color_init(black, 0, 0, 0);
        return black;
    }

    PreComputed *comps = precomputed_create(hit, r);
    return world_shade_hit(w, comps);
}

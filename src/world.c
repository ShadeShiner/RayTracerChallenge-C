#include <stdlib.h>
#include "world.h"
#include "lights.h"
#include "tuple.h"
#include "matrix.h"
#include "intersections.h"
#include "ray.h"
#include "shape.h"
#include "sphere.h"
#include "material.h"


/* List Interface */
void list_init(List *list)
{
    list->head = 0;
    list->tail = 0;
    list->size = 0;
}

int list_add(List *list, ListNode *node, Shape *data)
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

int list_contains(List *list, Shape *data)
{
    ListNode *node;

    for (node = list->head; node; node = node->next)
    {
        if (node->data->ID == data->ID)
            return 0;
    }
    
    return -1;
}

/* World Interface */
void world_init(World *world)
{
    list_init(&world->objects);
    world->light = 0;
}

int world_default(World *world)
{
    world_init(world);

    Shape *s2 = sphere_create();
    matrix_scaling(array_mem(s2->transform), 0.5, 0.5, 0.5);
    if (world_add_object(world, (void *)s2) != 0)
        return -1;

    Shape *s1 = sphere_create();
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


int world_add_object(World * world, Shape *shape)
{
    return list_add(&world->objects, 0, shape);
}


Shape*
world_get_object(World *world, unsigned int index)
{
    ListNode *element;
    unsigned i;
    for (element = world->objects.head, i = 0;
         i < index;
         element = element->next, ++i);
    
    return (Shape *)element->data;
}


int world_has_object(World *world, Shape *shape)
{
    return list_contains(&world->objects, shape);
}


IntersectGroup* world_intersect(World *w, Ray *r)
{
    IntersectGroup *xs = malloc(sizeof(IntersectGroup));

    ListNode *element;
    for (element = list_head(&w->objects); element; element = element->next)
    {
        Shape *shape = (Shape *)list_data(element);
        shape->intersect(shape, xs, r);
    }

    return xs;
}


Color*
world_shade_hit(World *w, PreComputed *comps)
{
    int in_shadow = world_is_shadowed(w, comps->over_point, comps->object);
    return material_lighting(comps->object->material,
                             w->light,
                             comps->over_point, comps->eyev, comps->normalv,
                             in_shadow);
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


int world_is_shadowed(World *w, Point *p, Shape *shape)
{
    Vector v;
    vector_sub(&v, w->light->position, p);

    float distance = vector_magnitude(&v);

    Vector direction;
    vector_normalize(&direction, &v);

    Ray r;
    ray_init(&r, p, &direction);

    IntersectGroup *intersections = world_intersect(w, &r);

    IntersectNode *node = intersections->front;
    Intersect *h;
    for(; node != NULL; node = node->next)
    {
        h = node->element;
        if (h->t > 0 && shape == NULL)
            break;
        /* This checks is to prevent self shadowing */
        if (h->t > 0 && shape != NULL && h->object->ID != shape->ID)
            break;
    }

    if (node == NULL)
        return 0;
    
    // TODO: Mostly likely this check is completely unnecessary
    int result;
    if (shape)
        result = h != 0 && h->t < distance && h->object->ID != shape->ID;
    else
        result = h != 0 && h->t < distance;
    
    return result;
}

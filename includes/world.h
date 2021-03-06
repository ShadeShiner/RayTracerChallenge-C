#ifndef WORLD_H
#define WORLD_H

#include "ray.h"
#include "lights.h"
#include "intersections.h"


/* Forward Declarations */
typedef struct Tuple_ Color;

/* List type declaration */

typedef struct ListNode_
{
    void *data;
    struct ListNode_ *next;
} ListNode;

typedef struct List_
{
    ListNode *head;
    ListNode *tail;
    int size;
    int (*compare)(const void *data1, const void *data2);
} List;

/* List Interface */
void list_init(List *list,
               int (*compare)(const void *data1, const void *data2));

int list_add(List *list, ListNode *node, void *data);

int list_contains(List *list, const void *data);

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_data(list) ((list)->data)

#define list_size(list) ((list)->size)

/* World type declaration */

typedef struct World_
{
    List objects;
    PointLight *light;
} World;

/* World Interface */
void world_init(World *world);

int world_default(World *world);

int world_add_object(World *world, void *object);

Sphere* world_get_object(World *world, unsigned int index);

int world_has_object(World *world, const void *object);

IntersectGroup* world_intersect(World *w, Ray *r);

Color* world_shade_hit(World *w, PreComputed *comps);

Color* world_color_at(World *w, Ray *r);

/* NOTE: This is different from the book. The math included in the book
does not help in solving the issue. I've attempted to switch the data type
from floats to doubles, but it seem to increase the acne instead. It seems
to be greatly affected by the epsilon as well so I made slight changes to
fix the issue. The only way I can fix the issue is to pass in the shape
to NOT check to complete avoid the self shadowing */
int world_is_shadowed(World *w, Point *p, Sphere *shape);

#define world_objects(world) ((world)->objects)

#define world_light(world) ((world)->light)

#endif
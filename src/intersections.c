#include <stdlib.h>
#include <stdarg.h>
#include <intersections.h>
#include <sphere.h>


/* Intersections */
void intersect_group_init(IntersectGroup *intersect_group)
{
	intersect_group->count = 0;
	intersect_group->front = NULL;
}

static void add_to_group(IntersectGroup *intersect_group, IntersectNode *node)
{
	if (intersect_group->front == NULL)
		intersect_group->front = node;
	else
	{
		IntersectNode *current, *prev;
		for (current = intersect_group->front, prev = NULL;
		     current != NULL;
			 prev = current, current = current->next)
		{
			if (node->element->t <= current->element->t)
			{
				node->next = current;
				if (prev == NULL)
					intersect_group->front = node;
				else
					prev->next = node;
				break;
			}
		}
		if (current == NULL)
			prev->next = node;
	}
	intersect_group->count++;
}

void intersect_group_add(IntersectGroup *intersect_group, int args, ...)
{
	va_list ap;
	va_start(ap, args);

	for (int i = 0; i < args; ++i)
	{
		IntersectNode *node = malloc(sizeof(IntersectNode));
		intersect_node_init(node, va_arg(ap, Intersect *));
		add_to_group(intersect_group, node);

	}

	va_end(ap);
}


Intersect* intersect_group_get(IntersectGroup *intersect_group, unsigned int index)
{
	if (index >= intersect_group->count)
		return NULL;
	
	IntersectNode *node = intersect_group->front;
	for (int i = 0; i < index; ++i)
		node = node->next;
	
	return node->element;
}


Intersect* intersect_group_hit(IntersectGroup *intersect_group)
{
	IntersectNode *node = intersect_group->front;
	for(; node != NULL; node = node->next)
		if (node->element->t >= 0)
			return node->element;
	return NULL;
}


/* IntersectNode */
void intersect_node_init(IntersectNode *node, Intersect *intersect)
{
	node->element = intersect;
	node->next = NULL;
}


/* Intersect */
void intersect_init(Intersect *intersect, float t, Sphere *s)
{
	intersect->t = t;
	intersect->object = s;
}


/* PreComputed */
PreComputed* precomputed_create(Intersect *intersection, Ray *ray)
{
	/* Instantiate a data structure for storing some precomputed values */
	PreComputed *result = (PreComputed *)malloc(sizeof(PreComputed));
	result->point   = malloc(sizeof(Point));
	result->eyev    = malloc(sizeof(Vector));
	result->normalv = malloc(sizeof(Vector));

	/* Copy the intersection's properties, for convenience */
	result->t = intersection->t;
	result->object = intersection->object;

	/* precomputed some useful values */
	ray_position(result->point, ray, intersection->t);
	vector_neg(result->eyev, ray->direction);
	sphere_normal_at(result->normalv, intersection->object, result->point);

	if (tuple_dot(result->normalv, result->eyev) < 0)
	{
		result->inside = 1;
		vector_neg(result->normalv, result->normalv);
	}
	else
	{
		result->inside = 0;
	}

	return result;
}

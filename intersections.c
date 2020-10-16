#include <stdlib.h>
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
		IntersectNode *current, *next;
		for (current = intersect_group->front, next = NULL;
		     current != NULL;
			 current = next)
		{
			next = current->next;
			if (node->element->t >= current->element->t)
			{
				node->next = current->next;
				current->next = node;
				break;
			}
		}
	}
	intersect_group->count++;
}

void intersect_group_add(IntersectGroup *intersect_group, Intersect *i1, Intersect *i2)
{
	IntersectNode *in1 = malloc(sizeof(IntersectNode));
	intersect_node_init(in1, i1);
	add_to_group(intersect_group, in1);

	IntersectNode *in2 = malloc(sizeof(IntersectNode));
	intersect_node_init(in2, i2);
	add_to_group(intersect_group, in2);
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


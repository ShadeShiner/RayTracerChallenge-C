#include <stdlib.h>
#include <intersections.h>
#include <sphere.h>


/* Intersections */
void intersections_init(Intersections *intersections)
{
	intersections->count = 0;
	intersections->front = NULL;
}

static void add_to_intersections(Intersections *intersections, IntersectNode *node)
{
	if (intersections->front == NULL)
		intersections->front = node;
	else
	{
		IntersectNode *current, *next;
		for (current = intersections->front, next = NULL;
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
	intersections->count++;
}

void intersections(Intersections *intersections, Intersect *i1, Intersect *i2)
{
	IntersectNode *in1 = malloc(sizeof(IntersectNode));
	intersect_node_init(in1, i1);
	add_to_intersections(intersections, in1);

	IntersectNode *in2 = malloc(sizeof(IntersectNode));
	intersect_node_init(in2, i2);
	add_to_intersections(intersections, in2);
}


Intersect* intersections_get(Intersections *intersections, unsigned int index)
{
	if (index >= intersections->count)
		return NULL;
	
	IntersectNode *node = intersections->front;
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


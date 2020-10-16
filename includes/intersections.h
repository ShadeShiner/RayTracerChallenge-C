#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

/* Forward Delcaration to avoid circular dependency includes */
typedef struct Sphere_ Sphere;

typedef struct IntersectGroup_ IntersectGroup;
typedef struct Intersection_ Intersection;
typedef struct IntersectNode_ IntersectNode;


struct Intersection_
{
	float points[2];
	unsigned short count;
};


/* 
   TODO: This will be a linked list where the it is sorted
   by their t valuse of each intersect object.
*/
struct IntersectGroup_
{
	unsigned int count;
	IntersectNode *front;
};


/* TODO: This will eventially replace Intersection_ */
typedef struct Intersect_
{
	float t;
	Sphere *object;
} Intersect;


struct IntersectNode_
{
	Intersect *element;
	IntersectNode *next;
};


/* IntersectGroup */
void intersect_group_init(IntersectGroup *intersections);

void intersect_group_add(IntersectGroup *intersections, int args, ...);

Intersect* intersect_group_get(IntersectGroup *intersect_group, unsigned int index);

Intersect* intersect_group_hit(IntersectGroup *intersect_group); 

/* IntersectNode */
void intersect_node_init(IntersectNode *node, Intersect *intersect);


/* Intersect */
void intersect_init(Intersect *intersect, float t, Sphere *s);

#endif

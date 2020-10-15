#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

/* Forward Delcaration to avoid circular dependency includes */
typedef struct Sphere_ Sphere;

typedef struct Intersection_ Intersection;
typedef struct Intersections_ Intersections;
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
struct Intersections_
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


/* Intersections */
void intersections_init(Intersections *intersections);

void intersections(Intersections *intersections, Intersect *i1, Intersect *i2);

Intersect* intersections_get(Intersections *intersections, unsigned int index);


/* IntersectNode */
void intersect_node_init(IntersectNode *node, Intersect *intersect);


/* Intersect */
void intersect_init(Intersect *intersect, float t, Sphere *s);

#endif

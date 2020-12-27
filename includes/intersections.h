#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

/* Forward Delcaration to avoid circular dependency includes */
typedef struct Sphere_ Sphere;
typedef struct Ray_ Ray;
typedef struct Tuple_ Point;
typedef struct Tuple_ Vector;

typedef struct IntersectGroup_ IntersectGroup;
typedef struct IntersectNode_ IntersectNode;
typedef struct PreComputed_ PreComputed;


/* NOTE: Will probably want to switch this to a generic Linked List? */
struct IntersectGroup_
{
	unsigned int count;
	IntersectNode *front;
};


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


struct PreComputed_
{
	float   t;
	Sphere  *object;
	Point   *point;
	Vector  *eyev;
	Vector  *normalv;
	int     inside;

	Point   *over_point;
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

/* PreComputed */
PreComputed* precomputed_create(Intersect *intersection, Ray *ray);

#endif

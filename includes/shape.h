#ifndef SHAPE_H
#define SHAPE_H


/* Forward declaraction(s) */
typedef struct Shape_ Shape;
typedef float Matrix;
typedef struct Material_ Material;
typedef struct Ray_ Ray;
typedef struct IntersectGroup_ IntersectGroup;


/* Structure */
struct Shape_
{
    void *derived;
    unsigned int ID;
    Matrix       transform[4][4];
    Material     *material;

    /* Function Pointers */
    void (*release)(Shape *shape);
    void (*destroy)(Shape *shape);

    int  (*equal)(Shape *s1, Shape*s2);

    void (*set_transform)(Shape *shape, Matrix *transform);
    void (*world_to_local)(Shape *shape, Ray *object, Ray *world);

    int  (*intersect)(Shape *shape, IntersectGroup *intersections, Ray *world_ray);
    void (*local_intersect)(Shape *shape, IntersectGroup *intersections, Ray *shape_ray);
};


/* Constructors */
unsigned int shape_init(Shape *shape);
Shape* shape_create();

/* Destructors */
void shape_release(Shape *shape);
void shape_destroy(Shape *shape);

/* Functions */
int  shape_equal(Shape *s1, Shape *s2);
void shape_set_transform(Shape *shape, Matrix *transform);
void convert_world_to_local_space(Shape *shape, Ray *local, Ray *world);
int shape_intersect(Shape *shape, IntersectGroup *intersections, Ray *world_ray);

#endif
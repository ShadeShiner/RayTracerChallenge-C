#ifndef CAMERA_H
#define CAMERA_H

#include "world.h"
#include "canvas.h"


// NOTE: Same type definition inside matrix.h
typedef float Matrix;

typedef struct Camera_
{
    unsigned int hsize;
    unsigned int vsize;

    float field_of_view;
	float half_width;
	float half_height;
	float pixel_size;

    Matrix transform[4][4];
} Camera;


/* Functions */
void camera_init(Camera *c,
                 unsigned int hsize, unsigned int vsize,
                 float field_of_view);

Canvas* camera_render(Camera *c, World *w);

#endif

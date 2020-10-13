#ifndef CANVAS_H
#define CANVAS_H

#include "tuple.h"

typedef struct Canvas_
{
	unsigned int width;
	unsigned int height;
	Color        *pixels;
} Canvas;


void canvas_init(Canvas *c, unsigned int width, unsigned height);

#define pixel_at(c, x, y) ((c)->pixels[(y) * (c)->width + (x)])

void write_pixel(Canvas *canvas, unsigned int x, unsigned int y, Color *color);

char * canvas_to_ppm(Canvas *canvas);

#endif

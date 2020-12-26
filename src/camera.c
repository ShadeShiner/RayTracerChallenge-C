#include <stdlib.h>
#include <math.h>

#include "camera.h"
#include "matrix.h"
#include "canvas.h"
#include "ray.h"


void camera_init(Camera *c,
                 unsigned int hsize, unsigned int vsize,
                 float field_of_view)
{
    c->hsize = hsize;
    c->vsize = vsize;
    c->field_of_view = field_of_view;
    matrix_identity(array_mem(c->transform), 4);

    float half_view = tanf(field_of_view / 2.0f);
	float aspect_ratio = (float)hsize / (float)vsize;

	/* Camera is wider than it is tall */
	if (aspect_ratio >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect_ratio;
	}
	/* Camera is taller than it is wide */
	else
	{
		c->half_width = half_view * aspect_ratio;
		c->half_height = half_view;
	}

	c->pixel_size = (c->half_width * 2) / (float)c->hsize;
}

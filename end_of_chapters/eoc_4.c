#include <stdio.h>
#include <math.h>
#include "canvas.h"
#include "matrix.h"
#include "tuple.h"


int main()
{
	Canvas canvas;
	canvas_init(&canvas, 400, 400);
	float radius = canvas.width * 3.0f/8.0f;
	float half = canvas.width / 2.0f;

	Color color;
	color_init(&color, 255, 255, 255);

	Matrix rotation;
	Point center, twelve, p;
	point_init(&center, 0, 0, 0); 
	point_init(&twelve, 0, 0, 1);

	for (int i = 0; i < 13; ++i)
	{
		matrix_rotation_y(&rotation, i * M_PI / 6);
		matrix_mul_tuple(&p, &rotation, &twelve);
		
		p.x = p.x * radius + half;
		p.z = canvas.height - (p.z * radius + half);
		write_pixel(&canvas, round(p.x), round(p.z), &color); 
	}
	char *ppm = canvas_to_ppm(&canvas);
	printf("%s", ppm);
}


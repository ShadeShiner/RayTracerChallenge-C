#include <stdio.h>
#include <tuple.h>
#include <canvas.h>
#include <sphere.h>


int main()
{
	/* start the ray at z = -5 */
	Point ray_origin;
	point_init(&ray_origin, 0, 0, -5);

	/* put the wall at z = 10 */
	float wall_z = 10;
	float wall_size = 7;

	int canvas_pixels = 100;
	/* Determine how large the pixels will be based on the canvas size and wall size */
	float pixel_size = wall_size / canvas_pixels;
	float half = wall_size / 2;

	Canvas canvas;
	Color color;
	Sphere shape;

	canvas_init(&canvas, canvas_pixels, canvas_pixels);
	color_init(&color, 1, 0, 0); /* red */
	sphere_init(&shape);

	/* for each row of pixels in the canvas */
	for (int y = 0; y < canvas_pixels; ++y)
	{
		/* compute the world y coordinate (top = +half, bottom = -half) */
		float world_y = half - pixel_size * y;

		/* for each pixel in the row */
		for (int x = 0; x < canvas_pixels; ++x)
		{
			/* compute the world x coordinate (left = -half, right = +half) */
			float world_x = -half + pixel_size * x;

			/* describe the point on the wall tha the ray will target */
			Point position;
			point_init(&position, world_x, world_y, wall_z);

			Ray r;
			Vector v, normalized_v;

			tuple_sub(&v, &position, &ray_origin);
			tuple_normalize(&normalized_v, &v);
			ray_init(&r, &ray_origin, &normalized_v);

			IntersectGroup xs;
			intersect_group_init(&xs);

			sphere_intersect(&xs, &shape, &r);

			if (intersect_group_hit(&xs) != NULL)
				write_pixel(&canvas, x, y, &color);
		}
	}

	char *ppm = canvas_to_ppm(&canvas);
	printf("%s", ppm);

	return 0;
}

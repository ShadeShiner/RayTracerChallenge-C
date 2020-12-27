#include <stdio.h>
#include <tuple.h>
#include <canvas.h>
#include <sphere.h>


int main()
{
	/* start the ray at z = -5 */
	Point ray_origin = {0, 0, -5};

	/* put the wall at z = 10 */
	float wall_z = 10;
	float wall_size = 7;

	int canvas_pixels = 100;
	/* Determine how large the pixels will be based on the canvas size and wall size */
	float pixel_size = wall_size / canvas_pixels;
	float half = wall_size / 2;

	Canvas canvas;
	canvas_init(&canvas, canvas_pixels, canvas_pixels);
	//Color color = {1, 0, 0}; /* red */
	
	/* 1. Assign material to sphere */
	Sphere shape;
	sphere_init(&shape);
	Color shape_color = {1, 0.2, 1};
	shape.material->color = &shape_color;

	/* 2. Add a light source */
	// Behind, above, and to the left of the eye
	Point light_position = {-10, 10, -10};
	// The light is white
	Color light_color = {1, 1, 1};
	PointLight light = {&light_position, &light_color};

	/* for each row of pixels in the canvas */
	for (int y = 0; y < canvas_pixels; ++y)
	{
		/* compute the world y coordinate (top = +half, bottom = -half) */
		float world_y = half - pixel_size * y;

		Point point;
		Vector normal, eye;
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
			Intersect *hit = intersect_group_hit(&xs);
			if (hit != NULL)
			{
				ray_position(&point, &r, hit->t); 
				sphere_normal_at(&normal, hit->object, &point);
				tuple_neg(&eye, r.direction);

				Color *color = material_lighting(hit->object->material, &light, &point, &eye, &normal, 0);
				write_pixel(&canvas, x, y, color);
			}
		}
	}

	char *ppm = canvas_to_ppm(&canvas);
	printf("%s", ppm);

	return 0;
}

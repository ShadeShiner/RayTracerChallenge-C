#include <stdio.h>
#include "tuple.h"
#include "canvas.h"


typedef struct Projectile_
{
	Point   *position;
	Vector  *velocity;
} Projectile;


typedef struct Environment_
{
	Vector *gravity;
	Vector *wind;
} Environment;


void tick(Projectile *p, Environment *e)
{
	tuple_add(p->position, p->position, p->velocity);

	Vector env_total;
	tuple_add(&env_total, e->gravity, e->wind);
	tuple_add(p->velocity, p->velocity, &env_total);
}


int main()
{
	Canvas c;
	Color red;
	Point start;
	Vector velocity, direction, gravity, wind;
	Projectile p;
	Environment e;

	// Canvas
	canvas_init(&c, 900, 550);

	// Color
	color_init(&red, 1.0f, 0.0f, 0.0f);

	// Projectile 
	point_init(&start, 0.0f, 1.0f, 0.0f);
	vector_init(&velocity, 1.0f, 1.8f, 0.0f);
	tuple_normalize(&velocity, &velocity);
	tuple_mul_scalar(&velocity, &velocity, 11.25);

	p.position = &start;
	p.velocity = &velocity;

	// Environment
	vector_init(&gravity, 0.0f, -0.1f, 0.0f);
	vector_init(&wind, -0.01f, 0.0f, 0.0f);

	e.gravity = &gravity;
	e.wind = &wind;

	while(p.position->y > 0 && p.position->x >= 0 && p.position->x < 900)
	{
		//printf("Pos: (%.2f, %.2f, %.2f)\n", p.position->x, p.position->y, p.position->z);
		// TODO: Flip the y position to go from bottom to top
		write_pixel(&c, (int)p.position->x, c.height - (int)p.position->y, &red);
		tick(&p, &e);
	}

	char *ppm = canvas_to_ppm(&c);
	printf("%s", ppm);
	
	/*
	canvas_init(&c, 2, 2);
	write_pixel(&c, 0, 0, &red);
	write_pixel(&c, 1, 1, &red);
	ppm = canvas_to_ppm(&c);
	printf("%s\n", ppm);
	*/

	return 0;
}

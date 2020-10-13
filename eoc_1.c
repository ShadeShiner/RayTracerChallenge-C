#include <stdio.h>
#include "tuple.h"


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
	Point start;
	Vector direction, gravity, wind;

	point_init(&start, 0.0f, 1.0f, 0.0f);
	vector_init(&direction, 1.0f, 1.0f, 0.0f);
	vector_init(&gravity, 0.0f, -0.1f, 0.0f);
	vector_init(&wind, -0.01f, 0.0f, 0.0f);

	Projectile p;
	p.position = &start;
	p.velocity = &direction;

	Environment e;
	e.gravity = &gravity;
	e.wind = &wind;

	while(p.position->y > 0)
	{
		printf("Pos: (%.2f, %.2f, %.2f)\n", p.position->x, p.position->y, p.position->z);
		tick(&p, &e);
	}

	return 0;
}

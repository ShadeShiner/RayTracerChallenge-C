#include <math.h>
#include <stdlib.h>
#include "tuple.h"


void tuple_init(Tuple *t, float x, float y, float z, float w)
{
	t->x = x;
	t->y = y;
	t->z = z;
	t->w = w;
}

/* Returns 0 if the two floats are within the epsilon, -1 if not */
int float_equal(float left, float right)
{
	if (abs(left - right) < EPSILON)
		return 0;

	return -1;
}

int tuple_equal(Tuple *left, Tuple *right)
{
	int result = float_equal(left->x, right->x);
	if (result)
		return -1;
	
	result = float_equal(left->y, right->y);
	if (result)
		return -1;

	result = float_equal(left->z, right->z);
	if (result)
		return -1;
	
	result = float_equal(left->w, right->w);
	if (result)
		return -1;
	
	return 0;
}

void tuple_add(Tuple *out, Tuple *left, Tuple *right)
{
	tuple_init(out,
			   left->x + right->x,
			   left->y + right->y,
			   left->z + right->z,
			   left->w + right->w);
}

void tuple_sub(Tuple *out, Tuple *left, Tuple *right)
{
	tuple_init(out,
			   left->x - right->x,
			   left->y - right->y,
			   left->z - right->z,
			   left->w - right->w);
}

void tuple_neg(Vector *out, Vector *v)
{
	tuple_init(out, -v->x, -v->y, -v->z, -v->w);
}

void tuple_mul_scalar(Tuple *out, Tuple *t, float scalar)
{
	tuple_init(out,
			   t->x * scalar,
			   t->y * scalar,
			   t->z * scalar,
			   t->w * scalar);
}

void color_mul(Color *out, Color *left, Color *right)
{
	color_init(out, color_red(left) * color_red(right),
	                color_green(left) * color_green(right),
					color_blue(left) * color_blue(right));
}

void tuple_div_scalar(Tuple *out, Tuple *t, float scalar)
{
	tuple_init(out,
			   t->x / scalar,
			   t->y / scalar,
			   t->z / scalar,
			   t->w / scalar);
}

float tuple_magnitude(Vector *v)
{
	return sqrt(v->x * v->x +
			    v->y * v->y +
			    v->z * v->z +
			    v->w * v->w);
}

void tuple_normalize(Vector *out, Vector *v)
{
	float magnitude = tuple_magnitude(v);
	tuple_init(out,
			   v->x / magnitude,
			   v->y / magnitude,
			   v->z / magnitude,
			   v->w / magnitude);
}

float tuple_dot(Vector *left, Vector *right)
{
	return left->x * right->x +
		   left->y * right->y +
		   left->z * right->z +
		   left->w * right->w;
}

void tuple_cross(Vector *out, Vector *left, Vector *right)
{
	vector_init(out, left->y * right->z - left->z * right->y,
					 left->z * right->x - left->x * right->z,
					 left->x * right->y - left->y * right->x);
}

/* MISC */

void tuple_reflect(Vector *out, Vector *in, Vector *normal)
{
	Vector product;

	float scalar_product = 2 * tuple_dot(in, normal);
	tuple_mul_scalar(&product, normal, scalar_product);
	tuple_sub(out, in, &product);
}


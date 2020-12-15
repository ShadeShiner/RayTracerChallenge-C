#ifndef TUPLE_H
#define TUPLE_H

#define EPSILON 0.00001

/* Structures */

typedef struct Tuple_
{
	float x;
	float y;
	float z;
	float w;
} Tuple;

typedef Tuple Point;

typedef Tuple Vector;

typedef Tuple Color;


/* Initializer */

void tuple_init(Tuple *t, float x, float y, float z, float w);

#define point_init(p, x, y, z) (tuple_init((p), (x), (y), (z), (1.0f)))

#define vector_init(v, x, y, z) (tuple_init((v), (x), (y), (z), (0.0f)))

#define color_init(c, r, g, b) (tuple_init((c), (r), (g), (b), (0.0f)))


/* Properties */

#define color_red(c) ((c)->x)
#define color_green(c) ((c)->y)
#define color_blue(c) ((c)->z)
#define color_alpha(c) ((c)->w)

#define color_set_red(color, r) ((color)->x = (r))
#define color_set_green(color,g) ((color)->y = (g))
#define color_set_blue(color, b) ((color)->z = (b))
#define color_set_alpha(color, a) ((color)->w = (a))

/* Equality */

int float_equal(float left, float right);

int tuple_equal(Tuple *left, Tuple *right);

#define point_equal tuple_equal

#define vector_equal tuple_equal

#define color_equal tuple_equal


/* Add */

void tuple_add(Tuple *out, Tuple *left, Tuple *right);

#define point_add tuple_add

#define vector_add tuple_add

#define color_add tuple_add


/* Subtraction */

void tuple_sub(Tuple *out, Tuple *left, Tuple *right);

#define point_sub tuple_sub

#define vector_sub tuple_sub

#define color_sub tuple_sub


void tuple_neg(Vector *out, Vector *v);

#define point_neg tuple_neg

#define vector_neg tuple_neg

#define color_neg tuple_neg

/* Multiplication */

void tuple_mul_scalar(Tuple *out, Tuple *t, float scalar);

#define color_mul_scalar tuple_mul_scalar

void color_mul(Color *out, Color *left, Color *right);

void tuple_div_scalar(Tuple *out, Tuple *t, float scalar);

/* Vector Operations */

float tuple_magnitude(Vector *v);

#define vector_magnitude tuple_magnitude

void tuple_normalize(Vector *out, Vector *v);

#define vector_normalize tuple_normalize

float tuple_dot(Vector *left, Vector *right);

#define vector_dot tuple_dot

void tuple_cross(Vector *out, Vector *left, Vector *right);

#define vector_cross tuple_cross

/* MISC */

void tuple_reflect(Vector *out, Vector *in, Vector *normal);

#define vector_reflect tuple_reflect

#endif

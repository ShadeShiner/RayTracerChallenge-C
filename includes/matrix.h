#ifndef MATRIX_H
#define MATRIX_H

#include "tuple.h"

/* Struct Declaration */

typedef struct Matrix_
{
	unsigned int size;
	float *matrix;
} Matrix;



/* Functions */

void matrix_init(Matrix *m, unsigned int size);

void matrix_identity(Matrix *m);

float matrix_get(Matrix *m, unsigned int row, unsigned int col);

void matrix_set(Matrix *m, unsigned int row, unsigned int col, float value);

int matrix_equal(Matrix *a, Matrix *b);

void matrix_mul(Matrix *m, Matrix *a, Matrix *b);

void matrix_mul_tuple(Tuple *out, Matrix *m, Tuple *t);

void matrix_transpose(Matrix *out, Matrix *in);

float matrix_determinant(Matrix *m);

void matrix_submatrix(Matrix *out, Matrix *in, int row, int col);

float matrix_minor(Matrix *m, int row, int col);

float matrix_cofactor(Matrix *m, int row, int col);

int matrix_inverse(Matrix *out, Matrix *in);

/* Transformations */

void matrix_translation(Matrix *out, float x, float y, float z);

void matrix_scaling(Matrix *out, float x, float y, float z);

void matrix_rotation_x(Matrix *out, float radians);

void matrix_rotation_y(Matrix *out, float radians);

void matrix_rotation_z(Matrix *out, float radians);

void matrix_shearing(Matrix *out, float xy, float xz, float yx, float yz, float zx, float zy);

#endif

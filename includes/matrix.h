#ifndef MATRIX_H
#define MATRIX_H

#include "tuple.h"

typedef float Matrix;

#define array_mem(m) (&m[0][0])

/* Functions */

void matrix_init(Matrix *m, unsigned int size);

void matrix_identity(Matrix *m, const unsigned int size);

#define matrix_get(m, row, col, size) (m[(row) * size + (col)])

#define matrix_set(m, row, col, size, value) (m[(row) * (size) + (col)] = (value))

int matrix_equal(Matrix *left, Matrix *right, const unsigned int size);

void matrix_mul(Matrix *m, Matrix *a, Matrix *b, const unsigned int size);

void matrix_mul_tuple(Tuple *out, Matrix *m, Tuple *t);

void matrix_transpose(Matrix *out, Matrix *in, const unsigned int size);

void matrix_submatrix(Matrix *out, Matrix *in, int row, int col, const unsigned int size);

float matrix_determinant(Matrix *m, const unsigned int size);

float matrix_minor(Matrix *m, int row, int col, const unsigned int size);

float matrix_cofactor(Matrix *m, int row, int col, const unsigned int size);

int matrix_inverse(Matrix *out, Matrix *in, const unsigned int size);

/* Transformations */

void matrix_translation(Matrix *out, float x, float y, float z);

void matrix_scaling(Matrix *out, float x, float y, float z);

void matrix_rotation_x(Matrix *out, float radians);

void matrix_rotation_y(Matrix *out, float radians);

void matrix_rotation_z(Matrix *out, float radians);

void matrix_shearing(Matrix *out, float xy, float xz, float yx, float yz, float zx, float zy);

#endif

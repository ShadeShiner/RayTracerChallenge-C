#include <stdlib.h>
#include <math.h>
#include "tuple.h"
#include "matrix.h"
#ifdef DEBUG
	#include <logger.h>
	char log_buffer[1024];
#endif


void matrix_init(Matrix *m, unsigned int size)
{
	m->size = size;
	m->matrix = (float *)malloc(size * size * sizeof(int));
}

void matrix_identity(Matrix *m)
{
	matrix_init(m, 4);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (i == j)
				matrix_set(m, i, j, 1);
			else
				matrix_set(m, i, j, 0);
}

float matrix_get(Matrix *m, unsigned int row, unsigned int col)
{
	int index = row * m->size + col;
	return m->matrix[index];
}

void matrix_set(Matrix *m, unsigned int row, unsigned int col, float value)
{
	int index = row * m->size + col;
	m->matrix[index] = value;
}

int matrix_equal(Matrix *a, Matrix *b)
{
	if (a->size != b->size)
		return 1;
	
	for (int i = 0; i < a->size; ++i)
	{
		for (int j = 0; j < a->size; ++j)
		{
			float m = matrix_get(a, i, j);
			float n = matrix_get(b, i, j);
			int result = float_equal(m, n);
			#ifdef DEBUG
				log_write("%s: (%d, %d) -> %f == %f = %d\n", __func__, i, j, 
						m, n, result);
			#endif
			if (result)
				return 1;
		}
	}
	return 0;
}

void matrix_mul(Matrix *m, Matrix *a, Matrix *b)
{
	matrix_init(m, 4);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float value = matrix_get(a, i, 0) * matrix_get(b, 0, j) +
						  matrix_get(a, i, 1) * matrix_get(b, 1, j) +
						  matrix_get(a, i, 2) * matrix_get(b, 2, j) +
					 	  matrix_get(a, i, 3) * matrix_get(b, 3, j);
			matrix_set(m, i, j, value);
		}
	}
}

void matrix_mul_tuple(Tuple *out, Matrix *m, Tuple *t)
{
	float values[4];
	for (int i = 0; i < 4; ++i)
	{
		values[i] = matrix_get(m, i, 0) * t->x +
					matrix_get(m, i, 1) * t->y +
					matrix_get(m, i, 2) * t->z +
					matrix_get(m, i, 3) * t->w;
	}
	tuple_init(out, values[0], values[1], values[2], values[3]);
}

void matrix_transpose(Matrix *out, Matrix *in)
{
	matrix_init(out, in->size);
	for (int i = 0; i < in->size; ++i)
		for (int j = 0; j < in->size; ++j)
		{
			float value = matrix_get(in, i, j);
			matrix_set(out, j, i, value);
		}
}

float matrix_determinant(Matrix *m)
{
	float det = 0;

	if (m->size == 2)
	{
		float a = matrix_get(m, 0, 0);
		float b = matrix_get(m, 0, 1);
		float c = matrix_get(m, 1, 0);
		float d = matrix_get(m, 1, 1);
		det = a * d - b * c;
	}
	else
	{
		for (int col = 0; col < m->size; ++col)
			det = det + matrix_get(m, 0, col) * matrix_cofactor(m, 0, col);
	}

	return det;
}

void matrix_submatrix(Matrix *out, Matrix *in, int row, int col)
{
	matrix_init(out, in->size - 1);
	int out_i = 0;
	int out_j = 0;
	for (int i = 0; i < in->size; ++i)
	{
		if (i == row)
			continue;
		for (int j = 0; j < in->size; ++j)
		{
			if (j == col)
				continue;
			float value = matrix_get(in, i, j);
			matrix_set(out, out_i, out_j++, value);
		}
		++out_i;
		out_j = 0;
	}
}

float matrix_minor(Matrix *m, int row, int col)
{
	Matrix sub_matrix;
	matrix_submatrix(&sub_matrix, m, row, col);
	float result = matrix_determinant(&sub_matrix);
	free(sub_matrix.matrix);
	return result;
}

float matrix_cofactor(Matrix *m, int row, int col)
{
	float minor = matrix_minor(m, row, col);
	return (row + col) % 2 == 0 ? minor : -minor;
}

int matrix_inverse(Matrix *out, Matrix *in)
{
	float det = matrix_determinant(in);
	if (det == 0)
		return 1;

	matrix_init(out, in->size);

	for (int i = 0; i < in->size; ++i)
	{
		for (int j = 0; j < in->size; ++j)
		{
			float c = matrix_cofactor(in, i, j);
			matrix_set(out, j, i, c / matrix_determinant(in));
		}
	}

	return 0;
}

/* Transformations */

void matrix_translation(Matrix *out, float x, float y, float z)
{
	matrix_identity(out);
	matrix_set(out, 0, 3, x);
	matrix_set(out, 1, 3, y);
	matrix_set(out, 2, 3, z);
}

void matrix_scaling(Matrix *out, float x, float y, float z)
{
	matrix_identity(out);
	matrix_set(out, 0, 0, x);
	matrix_set(out, 1, 1, y);
	matrix_set(out, 2, 2, z);
}

void matrix_rotation_x(Matrix *out, float radians)
{
	matrix_identity(out);
	matrix_set(out, 1, 1, cosf(radians));
	matrix_set(out, 1, 2, -sinf(radians));
	matrix_set(out, 2, 1, sinf(radians));
	matrix_set(out, 2, 2, cosf(radians));
}

void matrix_rotation_y(Matrix *out, float radians)
{
	matrix_identity(out);
	matrix_set(out, 0, 0, cosf(radians));
	matrix_set(out, 0, 2, sinf(radians));
	matrix_set(out, 2, 0, -sinf(radians));
	matrix_set(out, 2, 2, cos(radians));
}


void matrix_rotation_z(Matrix *out, float radians)
{
	matrix_identity(out);
	matrix_set(out, 0, 0, cosf(radians));
	matrix_set(out, 0, 1, -sinf(radians));
	matrix_set(out, 1, 0, sinf(radians));
	matrix_set(out, 1, 1, cosf(radians));
}

void matrix_shearing(Matrix *out, float xy, float xz, float yx, float yz, float zx, float zy)
{
	matrix_identity(out);
	matrix_set(out, 0, 1, xy);
	matrix_set(out, 0, 2, xz);
	matrix_set(out, 1, 0, yx);
	matrix_set(out, 1, 2, yz);
	matrix_set(out, 2, 0, zx);
	matrix_set(out, 2, 1, zy);
}


#include <stdlib.h>
#include <math.h>
#include "tuple.h"
#include "matrix.h"


void matrix_zero(Matrix *m, unsigned int size)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            m[i * size + j] = 0;
}


void matrix_identity(Matrix *m, const unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            unsigned int index = i * size + j;
            float value = i == j ? 1 : 0;
            m[index] = value;
        }
    }
}


int matrix_equal(Matrix *left, Matrix *right, const unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            float lvalue = matrix_get(left, i, j, size);
            float rvalue = matrix_get(right, i, j, size);

            int result = float_equal(lvalue, rvalue);
            if (result)
                return 1;
        }
    }

    return 0;
}


void matrix_mul(Matrix *m, Matrix *a, Matrix *b, const unsigned int size)
{
    for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float value = matrix_get(a, i, 0, size) * matrix_get(b, 0, j, size) +
						  matrix_get(a, i, 1, size) * matrix_get(b, 1, j, size) +
						  matrix_get(a, i, 2, size) * matrix_get(b, 2, j, size) +
					 	  matrix_get(a, i, 3, size) * matrix_get(b, 3, j, size);
			matrix_set(m, i, j, size, value);
		}
	}
}


void matrix_mul_tuple(Tuple *out, Matrix *m, Tuple *t)
{
	float values[4];
	for (int i = 0; i < 4; ++i)
	{
		values[i] = matrix_get(m, i, 0, 4) * t->x +
					matrix_get(m, i, 1, 4) * t->y +
					matrix_get(m, i, 2, 4) * t->z +
					matrix_get(m, i, 3, 4) * t->w;
	}
	tuple_init(out, values[0], values[1], values[2], values[3]);
}


void matrix_transpose(Matrix *out, Matrix *in, const unsigned int size)
{
	for (int i = 0; i < size; ++i)
    {
		for (int j = 0; j < size; ++j)
		{
			float value = matrix_get(in, i, j, size);
			matrix_set(out, j, i, size, value);
		}
    }
}


void matrix_submatrix(Matrix *out, Matrix *in, int row, int col, const unsigned int size)
{
	int out_i = 0;
	int out_j = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i == row)
			continue;
		for (int j = 0; j < size; ++j)
		{
			if (j == col)
				continue;
			float value = matrix_get(in, i, j, size);
			matrix_set(out, out_i, out_j++, size-1, value);
		}
		++out_i;
		out_j = 0;
	}
}


float matrix_determinant(Matrix *m, const unsigned int size)
{
    float det = 0;

	if (size == 2)
	{
		float a = matrix_get(m, 0, 0, size);
		float b = matrix_get(m, 0, 1, size);
		float c = matrix_get(m, 1, 0, size);
		float d = matrix_get(m, 1, 1, size);
		det = a * d - b * c;
	}
    else
	{
		for (int col = 0; col < size; ++col)
			det = det + matrix_get(m, 0, col, size) * matrix_cofactor(m, 0, col, size);
	}

	return det;
}


float matrix_minor(Matrix *m, int row, int col, const unsigned int size)
{
	Matrix sub_matrix[size-1][size-1];
	matrix_submatrix(array_mem(sub_matrix), m, row, col, size);
	float result = matrix_determinant(array_mem(sub_matrix), size-1);
	return result;
}


float matrix_cofactor(Matrix *m, int row, int col, const unsigned int size)
{
	float minor = matrix_minor(m, row, col, size);
	return (row + col) % 2 == 0 ? minor : -minor;
}


int matrix_inverse(Matrix *out, Matrix *in, const unsigned int size)
{
	float det = matrix_determinant(in, size);
	if (det == 0)
		return 1;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			float c = matrix_cofactor(in, i, j, size);
			matrix_set(out, j, i, size, c / matrix_determinant(in, size));
		}
	}

	return 0;
}

/* Transformations */

void matrix_translation(Matrix *out, float x, float y, float z)
{
	matrix_identity(out, 4);
	matrix_set(out, 0, 3, 4, x);
	matrix_set(out, 1, 3, 4, y);
	matrix_set(out, 2, 3, 4, z);
}

void matrix_scaling(Matrix *out, float x, float y, float z)
{
	matrix_identity(out, 4);
	matrix_set(out, 0, 0, 4, x);
	matrix_set(out, 1, 1, 4, y);
	matrix_set(out, 2, 2, 4, z);
}

void matrix_rotation_x(Matrix *out, float radians)
{
	matrix_identity(out, 4);
	matrix_set(out, 1, 1, 4, cosf(radians));
	matrix_set(out, 1, 2, 4, -sinf(radians));
	matrix_set(out, 2, 1, 4, sinf(radians));
	matrix_set(out, 2, 2, 4, cosf(radians));
}

void matrix_rotation_y(Matrix *out, float radians)
{
	matrix_identity(out, 4);
	matrix_set(out, 0, 0, 4, cosf(radians));
	matrix_set(out, 0, 2, 4, sinf(radians));
	matrix_set(out, 2, 0, 4, -sinf(radians));
	matrix_set(out, 2, 2, 4, cos(radians));
}


void matrix_rotation_z(Matrix *out, float radians)
{
	matrix_identity(out, 4);
	matrix_set(out, 0, 0, 4, cosf(radians));
	matrix_set(out, 0, 1, 4, -sinf(radians));
	matrix_set(out, 1, 0, 4, sinf(radians));
	matrix_set(out, 1, 1, 4, cosf(radians));
}

void matrix_shearing(Matrix *out, float xy, float xz, float yx, float yz, float zx, float zy)
{
	matrix_identity(out, 4);
	matrix_set(out, 0, 1, 4, xy);
	matrix_set(out, 0, 2, 4, xz);
	matrix_set(out, 1, 0, 4, yx);
	matrix_set(out, 1, 2, 4, yz);
	matrix_set(out, 2, 0, 4, zx);
	matrix_set(out, 2, 1, 4, zy);
}

void matrix_view_transformation(Matrix *out, Point *from, Point *to, Vector *up)
{
	/* Compute the forward vector and normalize it */
	Vector forward;
	vector_sub(&forward, to, from);
	Vector forward_normalized;
	vector_normalize(&forward_normalized, &forward);

	/* Compute the left vector */
	Vector up_normalized;
	vector_normalize(&up_normalized, up);
	Vector left;
	vector_cross(&left, &forward_normalized, &up_normalized);

	/* Compute the true_up vector */
	Vector true_up;
	vector_cross(&true_up, &left, &forward_normalized);

	/* Compute the orientation matrix with left, true_up, and forward vectors */
	Matrix orientation[4][4] = 
		{{left.x,     left.y,     left.z,     0},
		{true_up.x,  true_up.y,  true_up.z,  0},
		{-forward_normalized.x, -forward_normalized.y, -forward_normalized.z, 0},
		{0,          0,          0,          1}};

	/* Append translation to the orientation matrix to move the scene into place before entering */
	Matrix translation[4][4];
	matrix_translation(array_mem(translation), -from->x, -from->y, -from->z);
	matrix_mul(out, array_mem(orientation), array_mem(translation), 4);
}

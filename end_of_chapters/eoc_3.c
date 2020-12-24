#include <stdio.h>
#include "tuple.h"
#include "matrix.h"


void init_matrix_with_values_4(Matrix *m, float values[][4])
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			matrix_set(m, i, j, 4, values[i][j]);
}

void display_matrix(Matrix *m, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			printf("%f ", matrix_get(m, i, j, size));
		printf("\n");
	}
	printf("\n");
}

int main()
{
	/* 1 */
	printf("Question 1: What happens when you invert the identity matrix?\n");

	Matrix identity[4][4], inverse_identity[4][4];
	matrix_identity(array_mem(identity), 4);
	matrix_inverse(array_mem(inverse_identity), array_mem(identity), 4);	
	display_matrix(array_mem(inverse_identity), 4);

	/* 2 */
	printf("Question 2: What do you get when you multiply a matrix by its inverse?\n");
	Matrix inverse_m[4][4], result[4][4];
	Matrix m[4][4] = {{8, -5, 0, 2},
						  {7, 5, 6, 1},
						  {-6, 0, 9, 6},
						  {-3, 0, -9, -4}};
	matrix_inverse(array_mem(inverse_m), array_mem(m), 4);
	matrix_mul(array_mem(result), array_mem(m), array_mem(inverse_m), 4);
	display_matrix(array_mem(result), 4);

	/* 3 */
	printf("Question 3: Is there any difference between the *inverse* of the *transpose* of a matrix,"
		   "and the *transpose* of the *inverse*?\n");
	Matrix a[4][4], inverse_one[4][4], inverse_two[4][4];
	Matrix transpose_one[4][4], transpose_two[4][4];

	matrix_transpose(array_mem(transpose_one), array_mem(a), 4);
	matrix_inverse(array_mem(inverse_one), array_mem(transpose_one), 4);

	matrix_inverse(array_mem(inverse_two), array_mem(a), 4);
	matrix_transpose(array_mem(transpose_two), array_mem(inverse_two), 4);

	printf("Inverse of the Transpose\n");
	display_matrix(array_mem(inverse_one), 4);

	printf("Transpose of the Inverse\n");
	display_matrix(array_mem(transpose_two), 4);

	/* 4 */
	printf("Question 4: Try changing a single element of the identity matrix to a different number, "
		   "and then multiplying it by a tuple. What happens to the tuple?\n");
	Tuple t, t_result;
	tuple_init(&t, 1, 2, 3, 4);

	matrix_set(array_mem(identity), 1, 1, 4, 3);
	matrix_mul_tuple(&t_result, array_mem(identity), &t);
	printf("Tuple: (%f, %f, %f, %f)\n",
			t_result.x, t_result.y,
			t_result.z, t_result.w);

	return 0;
}

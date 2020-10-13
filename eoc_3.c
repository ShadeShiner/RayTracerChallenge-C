#include <stdio.h>
#include "tuple.h"
#include "matrix.h"


void init_matrix_with_values_4(Matrix *m, float values[][4])
{
	matrix_init(m, 4);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			matrix_set(m, i, j, values[i][j]);
}

void display_matrix(Matrix *m, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			printf("%f ", matrix_get(m, i, j));
		printf("\n");
	}
	printf("\n");
}

int main()
{
	/* 1 */
	printf("Question 1: What happens when you invert the identity matrix?\n");

	Matrix identity, inverse_identity;
	matrix_identity(&identity);
	matrix_inverse(&inverse_identity, &identity);	
	display_matrix(&inverse_identity, 3);

	/* 2 */
	printf("Question 2: What do you get when you multiply a matrix by its inverse?\n");
	Matrix m, inverse_m, result;
	float values[4][4] = {{8, -5, 0, 2},
						  {7, 5, 6, 1},
						  {-6, 0, 9, 6},
						  {-3, 0, -9, -4}};
	init_matrix_with_values_4(&m, values);
	matrix_inverse(&inverse_m, &m);
	matrix_mul(&result, &m, &inverse_m);
	display_matrix(&result, 3);

	/* 3 */
	printf("Question 3: Is there any difference between the *inverse* of the *transpose* of a matrix,"
		   "and the *transpose* of the *inverse*?\n");
	Matrix a, inverse_one, inverse_two;
	Matrix transpose_one, transpose_two;

	init_matrix_with_values_4(&a, values);
	matrix_transpose(&transpose_one, &a);
	matrix_inverse(&inverse_one, &transpose_one);

	matrix_inverse(&inverse_two, &a);
	matrix_transpose(&transpose_two, &inverse_two);

	printf("Inverse of the Transpose\n");
	display_matrix(&inverse_one, 3);

	printf("Transpose of the Inverse\n");
	display_matrix(&transpose_two, 3);

	/* 4 */
	printf("Question 4: Try changing a single element of the identity matrix to a different number, "
		   "and then multiplying it by a tuple. What happens to the tuple?\n");
	Tuple t, t_result;
	tuple_init(&t, 1, 2, 3, 4);

	matrix_set(&identity, 1, 1, 3);
	matrix_mul_tuple(&t_result, &identity, &t);
	printf("Tuple: (%f, %f, %f, %f)\n",
			t_result.x, t_result.y,
			t_result.z, t_result.w);

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 4
int path_exists(int mat[][N], int rows, int cols);
void main()
{
	int mat[N][N];
	printf("enter numbers for %d X %d  matrix: \n", N, N);
	for (int i = 0; i < N; i++)
	{
		printf("enter %d the %d row\t", N, i + 1);
		for (int j = 0; j < N; j++)
		{
			scanf(" %d", &mat[i][j]);
		}
	}
	int res = path_exists(mat, N, N);
	if (res)
		printf("there is a path");
	else
		printf("there is no path");
}

int path_exists(int mat[][N], int rows, int cols)
{
	if (!rows) return 1;
	if (!mat[rows - 1][cols - 1]) return 0;
	if (mat[rows - 2][cols - 1])
		return path_exists(mat, --rows, cols);
	if (mat[rows - 2][cols - 2])
		return path_exists(mat, --rows, --cols);
	if (mat[rows - 1][cols - 2])
		return path_exists(mat, rows, --cols);
	return 0;
}
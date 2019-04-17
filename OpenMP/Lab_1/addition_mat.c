#include <stdio.h>
#include <omp.h>

#define MAT_SIZE 400
#define MAT_VAL 99999.99999

int main(void) 
{
	long double a[MAT_SIZE][MAT_SIZE] = {MAT_VAL};
	long double b[MAT_SIZE][MAT_SIZE] = {MAT_VAL};
	long double result[MAT_SIZE][MAT_SIZE];

	double start, end;

	int threads[] = {1, 2, 4, 6, 8, 10, 12, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62};

	for(int k=0; k<20; k++)
	{
		start = omp_get_wtime();
		#pragma omp parallel for num_threads(threads[k])
			for(int i=0; i<MAT_SIZE; i++)
			{
				for(int j=0; j<MAT_SIZE; j++)
				{
					result[i][j] = a[i][j] + b[i][j];
				}
			}	
		end = omp_get_wtime();
	
		printf("%d\t%lf\n", threads[k], end - start);	
	}

}
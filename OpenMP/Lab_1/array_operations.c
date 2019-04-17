#include <stdio.h>
#include <omp.h>

#define ARR_SIZE 200000
#define ARR_VAL 99999.99999

int main(void) 
{
	long double a[ARR_SIZE] = {ARR_VAL};
	long double b[ARR_SIZE] = {ARR_VAL};

	double start, end;

	int threads[] = {1, 2, 4, 6, 8, 10, 12, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62};

	for(int k=0; k<20; k++)
	{
		start = omp_get_wtime();
		#pragma omp parallel for num_threads(threads[k])
			for(int i=0; i<ARR_SIZE; i++)
			{
				a[i] = (i+1) * 1.0;
				b[i] = (i+1) * 2.0;
			}	
		end = omp_get_wtime();
	
		printf("%d\t%lf\n", threads[k], end - start);	
	}

}
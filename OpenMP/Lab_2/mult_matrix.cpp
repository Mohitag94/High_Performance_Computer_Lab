#include <omp.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <assert.h>


using namespace std;
#define READ(f) freopen(f, "r", stdin)
#define WRITE(f) freopen(f, "w", stdout)
#define pks printf("Case %d: ",++ks);

#define mx 1002
int m=400,n=500;
int a[mx][mx];
int b[mx][mx];
int c[mx][mx];
int d[mx][mx];
int i,j,k;
void generate_matrix(int m, int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=rand()%100;
			b[i][j]=rand()%100;
			
		}
	}
		for(i=0;i<n;i++)
		{
		for(j=0;j<m;j++)
		{
			
			b[i][j]=rand()%100;
			
		}
		}
}
void check(int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		assert(c[i][j]==d[i][j]);
	}
}
void matrix_mult_serial(int m,int n)
{
	int i,j,k;
	double st=omp_get_wtime();
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<m;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	double en=omp_get_wtime();
	printf("Serial: %lf\n",en-st);
}



int main() {

	;
	generate_matrix(m,n);
	matrix_mult_serial(m,n);
	int threads[] = {1, 2, 4, 6, 8, 10, 12, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62};
	printf("row major \n");
	for(int i=0; i<20; i++)
	{	memset(d,0,sizeof d);
		double st=omp_get_wtime();
		#pragma omp parallel for num_threads(threads[i])  private(i,j,k)shared(a,b,c)
		for(i=0;i<m;i++)
		for( j=0;j<n;j++)
		for(k=0;k<m;k++)
		d[i][j]+=a[i][k]*b[k][j];
		double en=omp_get_wtime();
			check(n);
		printf("   %lf\n" ,en-st);						
	}
	printf("col major \n");
	for(int i=0; i<20; i++)
	{	memset(d,0,sizeof d);
		double st=omp_get_wtime();
		#pragma omp parallel for num_threads(threads[i])  private(i,j,k)shared(a,b,c)
		for(j=0;j<m;j++)
		for( i=0;i<n;i++)
		for(k=0;k<m;k++)
		d[i][j]+=a[i][k]*b[k][j];
		double en=omp_get_wtime();
			check(n);
		printf("   %lf\n",en-st);			
	}
	
	return 0;
	
}

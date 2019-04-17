#include <stdio.h>
#include <omp.h>
#include <time.h>
#include<stdlib.h>

int main()
{
	int first[384][512], second[384][512], third[384][512];
	int c,d;
	int red[384][512], green[384][512], blue[384][512];

	FILE* fpg,*fpr,*fpb;
	fpg=fopen("green.txt","r");
	fpr=fopen("red.txt","r");
	fpb=fopen("blue.txt","r");

	int i,j,k,l;

	for(i=0;i<384;i++)
		for(j=0;j<512;j++)
		{
			fscanf(fpg,"%d",&third[i][j]);
			fscanf(fpr,"%d",&first[i][j]);
			fscanf(fpg,"%d",&second[i][j]);
		}

	int threads[] = {1, 2, 4, 6, 8, 10, 12, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62};
 
	for(int m=0; m<20; m++)
	{
	   float start=omp_get_wtime();

		#pragma omp parallel sections num_threads(threads[m]) 
		{

			#pragma omp section
			{
			    for(i = 0; i < 384; ++i)
			        for(j = 0; j < 512; ++j)
					{
						if(i!=0 || i!=383 || j!=0 ||j!=511)
			   			{	
							int sum=0;
			                for(k=i-1;k<=i+1;k++)
			                    for(l=j-1;l<=j+1;l++)
								{
									sum=sum+first[k][l];
								}
						sum=sum/9;
						red[i][j]=sum;
						}
					}
			}

		#pragma omp section
		{
			for(i = 0; i < 384; ++i)
		        for(j = 0; j < 512; ++j)
				{
					if(i!=0 || i!=383 || j!=0 ||j!=511)
		            {
						int sum1=0;
		                for(k=i-1;k<=i+1;k++)
		                    for(l=j-1;l<=j+1;l++)
							{
								sum1=sum1+second[k][l];

							}
						sum1=sum1/9;
						blue[i][j]=sum1;
		             }
				}
		}

		#pragma omp section
		{
			for(i = 0; i < 384; ++i)
		        for(j = 0; j < 512; ++j)
				{
					if(i!=0 || i!=383 || j!=0 ||j!=511)
		            {
						int sum2=0;
		                for(k=i-1;k<=i+1;k++)
		                	for(l=j-1;l<=j+1;l++)
							{
								sum2=sum2+third[k][l];
							}
					sum2=sum2/9;
					green[i][j]=sum2;
					}	
				}
		}
	}       
	    
	float end=omp_get_wtime();
	float result=end-start;

	printf("%d Thread Takes\t%f Time\n", threads[m],result);
	    
	}
	 
	return 0;
}

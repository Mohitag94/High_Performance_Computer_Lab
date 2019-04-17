//minimum spanning tree using kruskal algorithm
#include <stdio.h>
#include <omp.h>

#define max 81
#define nodes 9

typedef struct edge
{
	int u, v, wt;
}edge;

typedef struct edgelist
{
	edge elist[max];//for storing the all the egdes with their weigths 
	int n;//for total number of edges in the graph 
}edgelist;

//nodelist will give all the edges in the graph..
//spanlist will give the minimum spannning edges for MST..
edgelist nodelist, spanlist;

//Graph taken form-->http://www.ggu.ac.in/download/Class-Note13/ds%20lecture%20notes%20graph12.11.13.pdf<--Fig.9.21-Page 7
int graph[nodes][nodes]= {{0,2,0,7,4,0,0,10,3},{2,0,2,0,7,4,0,0,6},{0,2,0,5,0,2,1,0,4},{7,0,5,0,0,0,6,5,1},{4,7,0,0,0,0,0,0,0},{0,0,2,0,0,0,0,0,0},{0,0,1,6,0,0,0,0,0},{10,0,0,5,0,0,0,0,0},{3,6,4,1,0,0,0,0,0}};

void edgelist_sort()
{
	//sorting the nodelsit
	int i, j;
	edge temp;

	for(i=0; i<nodelist.n; i++)
		for(j=i+1; j<nodelist.n; j++)
			if(nodelist.elist[i].wt > nodelist.elist[j].wt)
			{
				//performing swaping 
				temp = nodelist.elist[i];
				nodelist.elist[i] = nodelist.elist[j];
				nodelist.elist[j] = temp;
			}//end of if
}//end of sort_edgelsit()

void join_sets(int edge_belongs[], int s1, int s2)
{
	int i=0; 
	//will tell us if the copy of an egde exits in the nodelist..
	for(i=0; i<nodes; i++)
		if(edge_belongs[i]==s2)
			edge_belongs[i]==1;
}//end of union1()

int cost_calculation(int t)
{
	int i=0, cost=0;
	printf("\n********************************************************************\nThe Minimum Spanning Tree for thread %d\n", t);
	for(i=0; i<spanlist.n; i++)
	{
		printf("%d\t%d\t%d\n", spanlist.elist[i].u, spanlist.elist[i].v, spanlist.elist[i].wt);
		cost+=spanlist.elist[i].wt;
	}
	//printing the total cost 
	printf("\nThe Total Cost for the Graph is %d\n", cost);

	return cost;
}//end of cost_calculation()

void kruskal(int thread)
{
	int i, j;
	int edge_belongs[nodes];
	int set1, set2;
	#pragma omp parallel sections num_threads(thread) default(none) shared(graph, nodelist, spanlist, edge_belongs, set1, set2) private(i,j)
	{
		//getting all the edges from the graph given
		#pragma omp section
		{
			nodelist.n=0;

			for(i=0; i<nodes; i++)
			{
				for(j=0; j<nodes; j++)
				{
					if(graph[i][j]!=0)
					{
						nodelist.elist[nodelist.n].u = i;
						nodelist.elist[nodelist.n].v = j;
						nodelist.elist[nodelist.n].wt = graph[i][j];
						nodelist.n++;
					}//end of if
				}//end of for-j
			}//end of for-i

			//sorting the egdes according to increasing order of wieght
			edgelist_sort();
		}//end of parallel section-1

		#pragma omp section 
		{
			for(i=0; i<nodes; i++)
				edge_belongs[i] = i;//verties/node starts from 0 
		}//end of parallel section-2

		#pragma omp section
		{
			spanlist.n = 0;

			for(i=0; i<nodelist.n; i++)
			{
				set1 = edge_belongs[nodelist.elist[i].u];
				set2 = edge_belongs[nodelist.elist[i].v];
				
				if(set1 != set2)//avoiding the same node i.e 1,2 and 2,1(taking only one)
				{
					spanlist.elist[spanlist.n] = nodelist.elist[i];
					spanlist.n++;
					join_sets(edge_belongs, set1, set2);
				}//end of if 
			}//end of for-i
		}//end of parallel section-3
	}//end of the parallel code
}//end of kruskal()

int main()
{
	int i=0, j=0, total_cost=0;
	float total_time=0.0;
	//taking 20 threads.
	int threads[] = {1, 2, 4, 6, 8, 10, 12, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62};

	//printing the adjacent matrix.
	printf("\n*******KRUSKAL'S ALGOTITHM FOR MINIMUM SPANNING TREE USING OPENMP*******");
	printf("\nThe number of verties taken for the graph is 9.\n(Vertie starts from 0 to 8)\n********************************************************************\n");
	printf("\nThe Adjacent Matrix --\n");
	for(i=0; i<nodes; i++)
	{
		for(j=0; j<nodes; j++)
			printf("%d\t", graph[i][j]);
		printf("\n");
	}

	//running threads
	printf("\n********************************************************************\n");
	for(i=0; i<20; i++)
	{
		float start=omp_get_wtime();

		kruskal(threads[i]);

		float end=omp_get_wtime();
		float time=end-start;

		total_time+=time;
		//printing the egdes of MST along with their weigths
		total_cost+=cost_calculation(threads[i]);
		printf("%d Thread Takes\t%f Time\n", threads[i],time);
	}

	printf("\n********************************************************************\nThe Average Cost of MST for 20 different threads is %d\nThe Average Time taken by 20 different threads is %f", total_cost/20, total_time/20);
	printf("\n*******XXXXXX*******");
	return 0;
}//end of main()
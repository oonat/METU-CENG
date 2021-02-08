#include "the8.h"

// do not add extra libraries here


#define DEBUG 
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)

// for example usage of DEBUG macros check test.cpp

/*
Consider you are given a directed weighted graph G(V,E) with  N nodes and M edges and 2 source nodes as s1 and s2, 
and 2 destination nodes as d1 and d2. Assume that nodes represent locations and edges represent roads and weight is 
the distance (let's say in km) between the locations. We would like to transport some goods from s1 to d1 and s2 to d2. 
If we transport them separately the the cost is A per km. If we transport them together, 
then the cost is B per km (we know that A<B<2A), so that carrying them together will cost less when shared edges 
available on some part of the road. 

Determine and return the minimum total cost to perform 2 transportation operations from s1 to d1 and s2 to d2.

*/



int minCost(int**& graph, int V, int s1, int s2, int d1, int d2, int A, int B){
    int dist[V][V];
    
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++){
            if(graph[i][j] > 99)
                dist[i][j] = 100;
            else 
                dist[i][j] = graph[i][j];
        }
        
        
        
    for(int k = 0; k < V; k++)
        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }

    int min = A*(dist[s1][d1] + dist[s2][d2]);
    
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++){
            int val = A*(dist[s1][i] + dist[s2][i]) + B*dist[i][j] + A*(dist[j][d1] + dist[j][d2]);
            min = val < min ? val:min;
        }
        


                    
    return min;
}
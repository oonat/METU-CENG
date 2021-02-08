#include "the6.h"

/*

In this exam you are asked to find either strongly connected components or topological 
ordering of a given directed unweighted graph with node count as $n$.. 
For this, you first need to determine whether the graph is cyclic or not. 
If you determine that the graph has cycles you need to find strongly connected components, 
if it is a DAG then you need to find topological ordering of nodes.

You need to save the strongly connected components in the vector of vectors $scc$ 
such that each vector in $scc$ should contain node ids of a strongly connected component. 
In addition, you need to save the topological ordering of nodes in the vector $topSort$.

Note that the node ids in $scc$ and $topSort$ can be in any order.

*/


#define DEBUG 
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)

// for example usage of DEBUG macros check test.cpp


bool is_cyclic_util(int**& graph, int n, int node, int* color){
  color[node] = -1;

  for(int i = 0; i < n; i++){
    if(graph[node][i] == 1){
      if(color[i] == 0 && is_cyclic_util(graph, n, i, color))
        return true;
      else if(color[i] == -1)
        return true;
    }
  }
  color[node] = 1;
  return false;
}

bool is_cyclic(int**& graph, int n){
  int color[n];
  for(int i = 0; i < n; i++)
    color[i] = 0;
  
  for(int i = 0; i < n; i++)
    if(color[i] == 0)
      if(is_cyclic_util(graph, n, i, color))
        return true;

return false;
}


void topsort_util(int**& graph, int n, int node, bool* visited, stack<int>& Stack){
  visited[node] = true;

  for(int i = 0; i < n; i++)
    if(graph[node][i] == 1){
      if(!visited[i])
        topsort_util(graph, n, i, visited, Stack);
    }
  Stack.push(node);
}

void topsort_helper(int**& graph, int n, vector<int>& topSort){
  bool visited[n];
  for(int i = 0; i < n; i++)
    visited[i] = false;

  stack<int> Stack;
  
  for(int i = 0; i < n; i++)
    if(!visited[i])
      topsort_util(graph, n, i, visited, Stack);

  while (!Stack.empty()){
    topSort.push_back(Stack.top());
    Stack.pop();
  }
}


void dfs_visit(int**& graph, int n, int node, bool* visited, vector<int>& tmp){
  visited[node] = true;
  tmp.push_back(node);

  for(int i = 0; i < n; i++){
    if(graph[node][i] == 1 && !visited[i]){
      dfs_visit(graph, n, i, visited, tmp);
    }
  }

}

void dfs_rank(int**& graph, int n, int node, bool* visited, stack<int>& Stack){
  visited[node] = true;

  for(int i = 0; i < n; i++){
    if(graph[node][i] == 1 && !visited[i]){
      dfs_rank(graph, n, i, visited, Stack);
    }
  }

  Stack.push(node);
}


void transpose(int**& graph, int n){
  for(int i = 0; i < n; i++)
    for(int j = i; j < n; j++){
      int tmp = graph[i][j];
      graph[i][j] = graph[j][i];
      graph[j][i] = tmp;
    }
}


void scc_helper(int**& graph, int n, vector<vector<int>>& scc){
  bool visited[n];
  stack<int> Stack;

  for(int i = 0; i < n; i++)
    visited[i] = false;

  for(int i = 0; i < n; i++)
    if(!visited[i])
      dfs_rank(graph, n, i, visited, Stack);

  transpose(graph, n);

  for(int i = 0; i < n; i++)
    visited[i] = false;

  while (!Stack.empty()){ 
        int node = Stack.top(); 
        Stack.pop(); 
  
        if (!visited[node]){ 
          vector<int> tmp; 
          dfs_visit(graph, n, node, visited, tmp);
          scc.push_back(tmp);
        } 
    } 
}


void SCC_TopSort (int**& graph, int n, vector<vector<int>>& scc, vector<int>& topSort)
{
  if(is_cyclic(graph, n))
    scc_helper(graph, n, scc);
  else
    topsort_helper(graph, n, topSort);
}
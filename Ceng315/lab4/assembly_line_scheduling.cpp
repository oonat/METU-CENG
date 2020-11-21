#include <iostream>

/*
In this exam, you are asked to implement Assembly Line Scheduling problem in 3 different ways. In this problem there are 2 assembly lines. In the pipeline of the $n$ stations, each one of them has a particular work to accomplish. Parallel stations of assembly lines accomplish the same task in different times given in $a1[.]$ or $a2[.]$ depending on the which assembly line the station is in. In order to manufacture a car perfectly, it must pass through all of the stations.

When passed through a station $i$, it can continue on the next station $i+1$ in the same line without any extra cost or the line can be switched to the $i+1$th station of the other line incurring a cost given in $t1$ and $t2$ denoting cost of switching form line 1 to 2 and from line 2 to 1 respectively. In addition, there are two sets of costs, namely $e1,e2$ and $x1,x2$, representing entry and exit times of respective assembly lines. 

For quick checking of variables given:

    a1[i] :the time for line 1 station i to complete its task
    a2[i] :the time for line 2 station i to complete its task
    n      : number of stations in each assembly line 
    t1[i]  : cost of changing from line 1 station i to line 2 station i + 1
    t2[i]  : cost of changing from line 2 station i to line 1 station i + 1
    e1,e2    : cost of entry for assembly line 1,2 respectively, each > 0
    x1,x2    : cost of exit for assembly line 1,2 respectively, each > 0


 Your task is to implement 3 different ways to compute the minimum time for manufacturing a car. 

    You need to implement the recursive solution and return the optimal value and number of recursive calls ( it is easier to count at the exact time when the function starts executing)
    You need to implement the recursive+memoization solution and return the optimal value and number of recursive calls ( it is easier to count at the exact time when the function starts executing)
    You need to implement the tabulation solution and return the optimal value and number of total iterations in the tabulation loop 

     In each case, optimal value should be first of the pair to be returned whereas number of calls or loops are the second.

*/

#define DEBUG 
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)
#define min(x, y) (x < y ? x:y)


int recursion_helper(int line, int station, int*& a1, int*& a2, int*& t1, int*& t2, int e1, int e2, int& counter){
  counter++;

  if(station == 0)
    return line == 1 ? a1[0] + e1: a2[0] + e2;

  if(line == 1)
    return min(recursion_helper(1, station-1, a1, a2, t1, t2, e1, e2, counter), 
      recursion_helper(2, station-1, a1, a2, t1, t2, e1, e2, counter) + t2[station-1]) + a1[station];
  else
    return min(recursion_helper(1, station-1, a1, a2, t1, t2, e1, e2, counter) + t1[station-1], 
      recursion_helper(2, station-1, a1, a2, t1, t2, e1, e2, counter)) + a2[station];
}

int mem_recursion_helper(int line, int station, int* mem1, int* mem2, int*& a1, int*& a2, int*& t1, int*& t2, int e1, int e2, int& counter){
  counter++;

  if(line == 1){
    if(mem1[station])
      return mem1[station];
    else{
      if(station == 0)
        mem1[0] = a1[0] + e1;
      else
        mem1[station] = min(mem_recursion_helper(1, station-1, mem1, mem2, a1, a2, t1, t2, e1, e2, counter), 
          mem_recursion_helper(2, station-1, mem1, mem2, a1, a2, t1, t2, e1, e2, counter) + t2[station-1]) + a1[station];
    return mem1[station];
    }
  }else{
    if(mem2[station])
      return mem2[station];
    else{
      if(station == 0)
        mem2[0] = a2[0] + e2;
      else
        mem2[station] = min(mem_recursion_helper(1, station-1, mem1, mem2, a1, a2, t1, t2, e1, e2, counter) + t1[station-1], 
          mem_recursion_helper(2, station-1, mem1, mem2, a1, a2, t1, t2, e1, e2, counter)) + a2[station];
    return mem2[station];
    }
  }
}


std::pair<int,int> Assembly_Rec (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{

    std::pair<int,int> retVal;

    int counter = 0;
    int f1 = recursion_helper(1, n-1, a1, a2, t1, t2, e1, e2, counter);
    int f2 = recursion_helper(2, n-1, a1, a2, t1, t2, e1, e2, counter);

    retVal.first = min(f1 + x1, f2 + x2);
    retVal.second = counter;

    return retVal;
}

std::pair<int,int> Assembly_Memo (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{
    
    std::pair<int,int> retVal;

    int* mem1 = new int[n]{0};
    int* mem2 = new int[n]{0};

    int counter = 0;
    int f1 = mem_recursion_helper(1, n-1, mem1, mem2, a1, a2, t1, t2, e1, e2, counter);
    int f2 = mem_recursion_helper(2, n-1, mem1, mem2, a1, a2, t1, t2, e1, e2, counter);

    retVal.first = min(f1 + x1, f2 + x2);
    retVal.second = counter;

    delete[] mem1;
    delete[] mem2;
    
    return retVal;

}

std::pair<int,int> Assembly_Tab (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{
    
    std::pair<int,int> retVal;

    int f1[n], f2[n];
    f1[0] = e1 + a1[0];
    f2[0] = e2 + a2[0];

    for(int i = 1; i < n; i++){
      f1[i] = min(f1[i-1], f2[i-1] + t2[i-1]) + a1[i];
      f2[i] = min(f1[i-1] + t1[i-1], f2[i-1]) + a2[i];
    }

    retVal.first = min(f1[n-1] + x1, f2[n-1] + x2);
    retVal.second = n;
    
    return retVal;

}

int main() {

  int a1[] = {7,9,3,4,8}, a2[] = {8,5,6,4,5};
  int n = 5, e1 = 2, e2 = 4, x1 = 3, x2 = 6 ;
  int t1[] = {2,3,1,3}, t2[] = {2,1,2,2};
  int* p1 = a1, *p2 = a2, *p3 = t1, *p4 = t2;

  /*
  int a1[] = {4, 5, 3, 2}, a2[] = {2, 10, 1, 4};
  int n = 4, e1 = 10, e2 = 12, x1 = 18, x2 = 7  ;
  int t1[] = {7,4,5}, t2[] = {9,2,8};
  int* p1 = a1, *p2 = a2, *p3 = t1, *p4 = t2;
  */

  /*
  int a1[] = {4,5}, a2[] = {2,10};
  int n = 2, e1 = 2, e2 = 1, x1 = 1, x2 = 1 ;
  int t1[] = {2}, t2[] = {1};
  int* p1 = a1, *p2 = a2, *p3 = t1, *p4 = t2;
  */

  std::pair<int,int> tmp1  = Assembly_Rec(p1, p2, n, p3, p4, e1, e2, x1, x2);
  std::pair<int,int> tmp2  = Assembly_Memo(p1, p2, n, p3, p4, e1, e2, x1, x2);
  std::pair<int,int> tmp3  = Assembly_Tab(p1, p2, n, p3, p4, e1, e2, x1, x2);

  std::cout<<tmp1.first<<" "<<tmp1.second<<std::endl;
  std::cout<<tmp2.first<<" "<<tmp2.second<<std::endl;
  std::cout<<tmp3.first<<" "<<tmp3.second<<std::endl;

}
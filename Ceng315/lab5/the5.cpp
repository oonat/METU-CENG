#include "the5.h"

// do not add extra libraries here

/*
In this exam, you are asked to implement a decision making mechanism for stock buying from the financial market. Your aim is to find the investment that generates the best outcome for you.


For this, our AI module generated ( <$n1 x n2$> - <time x stocks> ) 2-d array $market$ where each $market[ i ][ j ]$ showing the future outcome of stock [ j ] if bought at time [ i ]. However, there are 3 rules in this market:

    You must buy only one stock at a given time (discrete time steps)
    You cannot buy a stock twice.
    You cannot buy a stock at a given time if a bigger id stock is already been bought in earlier time steps. (e.g. if you choose to buy stock 5 at time t=2, you cannot consider buying stocks 0,1,2,3 or 4 after that point, i.e. for t = 3,4 ...)

Your task is to generate a stock buying order sequence to maximize your outcome and fill the $solution$ vector with the order (with respect to their time steps, so order is important) and return the total outcome of that order.


*/


#define DEBUG 
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)

// for example usage of DEBUG macros check test.cpp


int BuyStocks (int**& market, int n1, int n2, vector<int>& solution)
{
  vector<vector<int>> table(n1, vector<int>(n2+1, -2000000)); // In case of INT_MIN usage, negative overflow happens



  for(int i = 1; i <= n2; i++){
    table[0][i] = table[0][i-1] < market[0][i-1]?market[0][i-1]:table[0][i-1];
  }

  
  for(int i = 1; i < n1; i++){
    for(int j = 1; j <=n2; j++){
      int val = table[i-1][j-1] + market[i][j-1];
      table[i][j] = table[i][j-1] < val ? val : table[i][j-1];
    }
  }

  int index = n2;
  for(int i = n1-1; i >= 0; i--){
    for(int j = index; 0 < j; j--){
      if(table[i][j] > table[i][j-1]){
        solution.insert(solution.begin(), j-1);
        index = j-1;
        break;
      }
    }
  }

  return table[n1-1][n2];
}
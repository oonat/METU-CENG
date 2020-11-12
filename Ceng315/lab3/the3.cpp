#include <cmath>


// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    size      : size of arr
    ascending : true for ascending, false for descending 
    
    you can use ceil function from cmath

    In this exam, you are asked to sort the given array $arr$ with Radix Sort ascending or descending depending on the boolean variable $ascending$ and return the number of iterations done in four loops of the Counting Sort algorithm (you need to use Counting Sort as a subroutine in the Radix Sort). $n$ is the number of elements. You are expected to use Counting Sort for $l$ digits at each time.
    
*/

void CountSort(long arr[], int n, int l, long exponent, bool ascending, int& counter){
  int wide = pow(10, l);
  int* C = new int[wide]{0};
  long* out = new long[n];

  if(ascending){
    for(int i = 0; i < n; i++){
      C[(arr[i] / exponent) % wide]++;
      counter++;
    }
  }else{
  for(int i = 0; i < n; i++){
      C[wide - (arr[i] / exponent) % wide -1]++;
      counter++;
  }
  }


  for(int i = 1; i < wide; i++){
    C[i] += C[i-1];
    counter++;
  }


  if(ascending){
  for(int i = n-1; i >= 0; i--){
      out[C[(arr[i] / exponent) % wide]-1] = arr[i];
      C[(arr[i] / exponent) % wide]--;
      counter++;
    }
  }else{
  for(int i = n-1; i >= 0; i--){
      out[C[wide - (arr[i] / exponent) % wide -1]-1] = arr[i];
      C[wide - (arr[i] / exponent) % wide -1]--;
      counter++;
    }
  }

  for(int i = 0; i < n; i++){
    arr[i] = out[i];
    counter++;
  }
  
  delete[] C;
  delete[] out;

}

int RadixSort(long arr[], bool ascending, int n, int l){
  int counter = 0;

  long exponent = 1;
  for(int k = 0; k < 12/l; k++){
    CountSort(arr, n, l, exponent, ascending, counter);
    exponent *= pow(10, l);
  }
  return counter;
}
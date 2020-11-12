#include "the1.h"

// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    size      : size of arr
    ascending : true for ascending, false for descending 
    
    you can use ceil function from cmath
    
*/
int merge_comparison_count = 0;

bool compare(int a, int b, bool ascending){
  merge_comparison_count++;
  return ascending ? (a < b) : (a > b);
}

void merge(int*& arr, int left, int mid, int right, bool ascending){

int leftsize = mid - left + 1;
int rightsize = right - mid;
int leftarray[leftsize];
int rightarray[rightsize];

if(left == right)
    return;

for(int i = 0; i < leftsize; i++)
  leftarray[i] = arr[left + i];

for(int j = 0; j < rightsize; j++)
  rightarray[j] = arr[mid + 1 + j];

int i = 0, j = 0, counter = left;

while(i < leftsize && j < rightsize){
  if(compare(leftarray[i],rightarray[j], ascending))
    arr[counter++] = leftarray[i++];
  else
    arr[counter++] = rightarray[j++];
}

for(; i < leftsize; i++)
  arr[counter++] = leftarray[i];

for(; j < rightsize; j++)
  arr[counter++] = rightarray[j];

}


void mergesort_helper(int*& arr, int start, int end, bool ascending){

  if(start < end){
    int mid = start + (end - start)/2;
    mergesort_helper(arr, start, mid, ascending);
    mergesort_helper(arr, mid + 1, end, ascending);

    merge(arr, start, mid, end, ascending);
  }
}


int MergeSort(int*& arr, int size, bool ascending)
{
  merge_comparison_count = 0;

  mergesort_helper(arr, 0, size-1, ascending);

  return merge_comparison_count;
}


int funky_comparison_count = 0;

bool funky_compare(int a, int b, bool ascending){
  funky_comparison_count++;
  return ascending ? (a < b) : (a > b);
}

void swap(int*& arr, int a, int b){
    int tmp = arr[b];
    arr[b] = arr[a];
    arr[a] = tmp;
}

void funky_helper(int*& arr, int first, int last, bool ascending){
    
  int size = last - first + 1;
  
  if(size <= 1)
    return;
    
  if(funky_compare(arr[last], arr[first], ascending))
    swap(arr, first, last);

  if(size >= 3){
    int part = ceil(size*2.0/3);
    funky_helper(arr, first, first + part - 1, ascending);
    funky_helper(arr, last - part + 1, last, ascending);
    funky_helper(arr, first, first + part - 1, ascending);
  }

}

int FunkySort(int*& arr, int size, bool ascending)
{
    funky_comparison_count = 0;

    funky_helper(arr, 0, size - 1, ascending);

    return funky_comparison_count;
}

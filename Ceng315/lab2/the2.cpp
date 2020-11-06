#include "the2.h"

// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    size      : size of arr
    ascending : true for ascending, false for descending 
    
    you can use ceil function from cmath
    
*/

int comp_num = 0;

bool compare(int a, int b, bool ascending){
  comp_num++;
  return ascending ? (a < b) : (a > b);
}

void swap(int*& arr, int a, int b){
  int tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}

int q_partition(int*& arr, int start, int end, bool ascending){
  int val = arr[end];
  int i = start - 1;
    int j = i + 1;

    while(j <= end - 1){
      if(compare(arr[j], val, ascending)){
          i += 1;
          swap(arr, i, j);
      }
      j += 1;
    }
    swap(arr, end, i + 1);

    return i + 1;
}

void q_helper(int*& arr, int start, int end, bool ascending){
  if(start < end){
    int position = q_partition(arr, start, end, ascending);
    q_helper(arr, start, position - 1, ascending);
    q_helper(arr, position + 1, end, ascending);
  }
}

int QuickSort (int*& arr, int size, bool ascending)
{ comp_num = 0;
  q_helper(arr, 0, size - 1, ascending);
  return comp_num;
}


void q3_partition_asc(int*& arr, int start, int end, int& pos1, int& pos2){
  int i = start, k = start, p = end;
  int m;

  while(i < p){
    if(arr[i] < arr[end]){
      comp_num++;
      swap(arr, i++, k++);
    }else if(arr[i] == arr[end]){
      comp_num+=2;
      swap(arr, i, --p);
    }else{ 
      i++;
      comp_num+=2;
    }
  }

  m = (p-k) < (end-p+1) ? (p-k):(end-p+1);
  for(int c = 1; c <=m; c++)
    swap(arr, k+c-1, end-m+c);
  
  pos1 = k;
  pos2 = p;
  
}

void q3_partition_desc(int*& arr, int start, int end, int& pos1, int& pos2){
  int i = start, k = start, p = end;
  int m;

  while(i < p){
    if(arr[i] > arr[end]){
      comp_num++;
      swap(arr, i++, k++);
    }else if(arr[i] == arr[end]){
      comp_num+=2;
      swap(arr, i, --p);
    }else{ 
      i++;
      comp_num+=2;
    }
  }

  m = (p-k) < (end-p+1) ? (p-k):(end-p+1);
  for(int c = 1; c <=m; c++)
    swap(arr, k+c-1, end-m+c);
  
  pos1 = k;
  pos2 = p;
  
}

void q3_helper(int*& arr, int start, int end, bool ascending){
  if(start < end){
    int pos1, pos2;

    if(ascending)
      q3_partition_asc(arr, start, end, pos1, pos2);
    else
      q3_partition_desc(arr, start, end, pos1, pos2);

    q3_helper(arr, start, pos1 - 1, ascending);
    q3_helper(arr, end - pos2 + pos1 + 1, end, ascending);
  }

}

int QuickSort3 (int*& arr, int size, bool ascending)
{ 
  comp_num = 0;
  q3_helper(arr, 0, size -1, ascending);
  return comp_num;
}

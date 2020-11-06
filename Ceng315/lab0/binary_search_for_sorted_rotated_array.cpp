/*

You are given an array and a number. Your task is to determine whether num is in the array and return the index of the number in the array. If the given number cannot be found, return -1;

The array has some specific properties. It contains unique elements without any duplicates. Additionally the elements are sorted in increasing order except  some of the values from one end may be moved to the other end without breaking their order internally. In other words, the array is rotated.

A trivial linear search implementation will  return the index in O(n) time, n being the size of the array.

We are looking for O(lg(n)) solutions for this task.

*/

int finder(std::vector<int>& arr, int key, int start, int end){

  // overflow checked
  int mid = start + (end - start)/2;

  if(arr[mid] == key)
    return mid;
  
  if(start == end)
    return -1;

  if(arr[mid] >= arr[start]){
    if(arr[start] <= key && key < arr[mid])
      return finder(arr, key, start, mid - 1);
    else
      return finder(arr, key, mid + 1, end);
  }

  else{
    if(arr[mid] < key && key <= arr[end])
      return finder(arr, key, mid + 1, end);
    else
      return finder(arr, key, start, mid - 1);
  }
}


int search(std::vector<int>& array, int num)
{   
    if(array.empty())
        return -1;
    else
        return finder(array, num, 0, array.size() - 1);
}

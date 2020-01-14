#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "the1_recursive.h"

#define MAX_CUST_REQUIREMENT 1000
#define MAX_SHIP_TYPE_COUNT 10
#define MAX_CUST_COUNT 10

/*
	+ Function arguments are:
		++ ship_types:				Array of ship types. Ship type is decided by ship capacity, it is a conceptual thing.
		++ ship_type_count:			Length of ship types array.
		++ customer_requirement:	Load requirement for a single customer.

	+ Returns:
		The minimum number of ships that are required to satisfy given customer load requirement.

	+ Recursive code should work fine with smaller values.
	When values get larger, recursive function returns after some considerable time.

	+ "return -1" is just a placeholder. Please change it after you implemented this function.
*/

int helper(int ship_types[], int ship_type_count, int customer_requirement,int k){

int i,min,now;

if(customer_requirement<0){
   return -1;
}
else if (customer_requirement == 0){
   return k;
}
else{

min = helper(ship_types,ship_type_count,customer_requirement-ship_types[0],k+1);

for(i=1;i<ship_type_count;i++){



  now = helper(ship_types,ship_type_count,customer_requirement-ship_types[i],k+1);

  if(now <min && now>0)
    min = now;


}

}

return min;


}



int min_ships_required_recursive(int ship_types[], int ship_type_count, int customer_requirement) {


return helper(ship_types,ship_type_count,customer_requirement,0);



}

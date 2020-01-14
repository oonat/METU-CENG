#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "the1_iterative.h"

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

	+ Iterative code should work fine with various input values.
	This is because in recursive one, you re-calculate things.
	In iterative one, you probably won't do re-calculation.

	+ "return -1" is just a placeholder. Please change it after you implemented this function.
*/
int min_ships_required_iterative(int ship_types[], int ship_type_count, int customer_requirement) {


    int array[2000000];
    int i=0,k;
    array[0] = 0;

    for(i=0;i<=customer_requirement;i++)
       array[i] = i;



    for(i=1;i<ship_type_count;i++){

    for(k=ship_types[i];k<=customer_requirement;k++){

    if(1+array[k-ship_types[i]]<array[k]){

       array[k] = 1+array[k-ship_types[i]];

    }



    }



    }



    return array[customer_requirement];


    }




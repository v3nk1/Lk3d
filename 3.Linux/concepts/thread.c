#include<stdio.h>
#include"list_tlib.h"

main(){

	list_t l1,l2;

	list_init(&l1);
	list_init(&l2);

	insert_first(&l1,2);
	insert_first(&l1,2);
	insert_first(&l1,2);
	insert_first(&l1,2);
	insert_first(&l1,2);
	insert_first(&l2,2);
	insert_first(&l2,2);
	insert_first(&l2,2);
	insert_first(&l2,2);
	insert_first(&l2,2);

	print(l1);
	print(l2);
	
}

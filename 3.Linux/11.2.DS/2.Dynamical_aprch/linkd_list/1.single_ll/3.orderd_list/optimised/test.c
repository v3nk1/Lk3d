#include"list.h"

main(){

	list_t l1,l2; 
	
	list_init(&l1);
	list_init(&l2);

	insert(&l1,10);
	insert(&l1,9);
	insert(&l1,5);
	insert(&l1,11);
	insert(&l2,6);
	insert(&l2,-1);
	insert(&l2,8);
	insert(&l2,-6);

	print(l1);
	print(l2);

	insert(&l1,5);
	insert(&l2,-6);

	print(l1);
	print(l2);

}

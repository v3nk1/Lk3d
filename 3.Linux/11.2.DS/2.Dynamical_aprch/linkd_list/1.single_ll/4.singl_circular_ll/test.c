#include"circular.h"

main(){

	circ_t c1,c2;

	circ_init(&c1);
	circ_init(&c2);


/*	if(insert_first(&c1,10)==-1) errmsg("insert");
	insert_first(&c1,20);
	insert_first(&c1,30);
	insert_first(&c1,40);
	insert_first(&c2,50);
	insert_first(&c2,60);
	insert_first(&c2,70);
	insert_first(&c2,80);

*/

	insert_last(&c1,10);
	insert_last(&c1,20);
	insert_last(&c1,30);
//	insert_last(&c1,40);
//	insert_last(&c1,50);

	print_circ(c1);
	print_circ(c2);

}

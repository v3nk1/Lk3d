
#include"queue.h"
#include"perror.h"

main(){

	fque_t que1,que2;
	
	fque_attr_t attr;

	if(fque_attr_setmax(&attr,2)<0) my_errmsg("fque_attr_setmax"); //ignored doent support
	
	fque_init(&que1,&attr); //no init invoked then undefined behaviour results //or declare it as global(global obj initial state is zero(no junk values as in local variables))..
	fque_init(&que2,&attr);

	enque(&que1,11);my_errmsg("enque");
	if(enque(&que1,20)<0) my_errmsg("enque");
	if(enque(&que1,30)<0) my_errmsg("enque");
	if(enque(&que2,40)<0) my_errmsg("enque");
	if(enque(&que2,50)<0) my_errmsg("enque");
	if(enque(&que2,60)<0) my_errmsg("enque");
	
	if(print_que(&que1) < 0) my_errmsg("print_que");
	fque_flush(&que1);  //it makes the que as fresh, all entities are new state(setted to 0)..
	
	printf("Q1: ");
	if(print_que(&que1) < 0) my_errmsg("print_que");

	printf("Q2: ");
	print_que(&que2);
	
	deque(&que1);my_errmsg("deque");
	deque(&que1);my_errmsg("deque");
	deque(&que1);my_errmsg("deque");
	deque(&que1);my_errmsg("deque");

	printf("Q1: ");
	print_que(&que1);my_errmsg("print_que");

}

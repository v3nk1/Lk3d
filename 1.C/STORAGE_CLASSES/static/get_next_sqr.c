// write a fun which will square the gven integer passed as argument, if passes 0 as argument return square of the incremented previous value;

#include<stdio.h>

int get_next_sqr(int x){

	static int pre_val;    //it is stored in bss segment.so we can update its value after initialisation.
	// static int pre_val=10; so it is stored in data segmet. so its a fixed value, we cannt update it.
	if(x>0) {
		pre_val=x; 
		return x*x;
		}
	else return (pre_val)*(++pre_val);

}

main(){

//get_next_sqr(3);
	printf("%d\n",get_next_sqr(3));
	printf("%d\n",get_next_sqr(0));
	printf("%d\n",get_next_sqr(0));
	printf("%d\n",get_next_sqr(10));
	printf("%d\n",get_next_sqr(0));

}

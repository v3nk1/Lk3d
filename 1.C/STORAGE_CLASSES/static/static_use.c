//prog to print how many times the stat_use function invoked.. by using a variable called static cnt; we can achieve this also by declaring cnt globally also..

#include<stdio.h>

void stat_use(void){

	static int cnt;
	cnt++;
	
	printf("stack use function invokde cnt times = %d\n",cnt);
}

void dummy_func(void){

	int dummy1=10;
	int dummy2=20;
	int dummy3=30;

}

main(){

	stat_use();
	dummy_func();//i'm calling these dummy functions becoz make sure that the stack is not destroyed, instead that replacement will happens.. if u dont use dummy_function the previous stack(memory for temparary variable cnt will be there untill any other local variable will came to stack )

	stat_use();	
	dummy_func();	
	dummy_func();	

	stat_use();	
	dummy_func();	
	dummy_func();	

	stat_use();	
	dummy_func();	
	dummy_func();	

	stat_use();	

}


/********************************************************************************************************************************

	REMOVE STATIC AND SEE THE RESULT..

	without static:
	``````````````` Some fortunate time the results will be come as required.
			in above case:
			``````````````	comment static keyword and
					comment all dummy_funcs calls in main thread
								and see the results..
				u may/maynot get as required..

			now:
			````		comment static keyword and 
					uncomment all dummy_funcs calls in main thread
                                                                and see the results..
				u wont get the required cnt value..

	with static:
	````````````
			in above case:
			`````````````` un comment static keyword and 
				       comment/uncomment all dummy_func calls in main thread
									and see the results..

					u will got required cnt value..

	Thats d use of static,
		(i) Without static its like a local variable means if the function execution completes then it is removed(means if any local variable came for storage purpose it can store here at in cnt place).

			scope    : is local to the block(function)
			lifetime : also block(function) after that function post-amble exectutes compiler free to remove it if 					   another local variable came for storing..

		(ii) With static it not like a local variable means if the function execution completes then it cannt freed(means if any local variable came for storage purpose it cannt store in cnt place). so in other memory other variable will be stored.

			See for static cnt at the time of declaration the memory allocated and it cannt be destroyed until the 				program	has terminated.
			
			scope   : is local to block(means varible name we can use is local)
			lifetime: is until the program terminated..

			STATIC ALSO LIKE GLOBAL DECLARATION..
			
			BUT FOR GLOBAL VARIABLE THOSE CAN BE ACCESSIBLE BY OTHER PROG ALSO BY DECLARIGN EXETERN IN THAT OTHER PROG			
			BUT HERE for STATIC symbols(variables/functions) THERE will b SECURITY WE CANN'T BE USED OUT OF THE PROG(so other prog cannt access it) since those will alive with in the program..
			

********************************************************************************************************************************/

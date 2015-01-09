/*Create a thread which will take following struct as argument
			struct msg{
				char buf[50];
				int len;
				};
	Thread shuld print the values of argument..

*/

#include<stdio.h>
#include<pthread.h>

struct msg{
	char buf[50];
	int len;
	};

void *threadFunc(void *obj){

	printf("buff: %s\n",((struct msg *)obj)->buf); // must type casted to structure data type..
	
	printf("len: %d\n",((struct msg *)obj)->len);

}

main(){

	pthread_t thread;
	
	struct msg obj={"venkatesh",9};
	
	pthread_create(&thread,NULL,threadFunc,&obj);

	pthread_join(thread,NULL);

}

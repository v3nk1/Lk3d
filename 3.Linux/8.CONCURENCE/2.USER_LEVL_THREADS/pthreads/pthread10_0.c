//prog to print the default stack-attributes..

#define _GNU_SOURCE  //used for pthread_getattr_np

#include<stdio.h>
#include<pthread.h>

#include<errno.h> //used for perror

void *threadFunc(void *arg){

	printf("thread has created successfully\n");
	sleep(10);

}

void print_stack_attr(pthread_attr_t attr){

	void *stackaddr;
	size_t stacksize;
	size_t gaurdsize;
		
	if(errno = pthread_attr_getstack(&attr,&stackaddr,&stacksize)) perror("pthread_attr_getstack"),exit(10);
	//pthread_attr_getstackaddr(&attr,&stackaddr); or u can use these also,but they are deprecated functions(in furuther extenctions these funtions are nomore). 
	//pthread_attr_getstacksize(&attr,&stacksize);

	printf("stack starting/ending address: %p/%p\n",(char *)stackaddr,(char *)stackaddr + stacksize);
	printf("stack size:%lu bytes\n",stacksize);

	pthread_attr_getguardsize(&attr,&gaurdsize);
	printf("gaurd size:%lu bytes\n",gaurdsize);

}

main(){
	
	pthread_t tid;
	static pthread_attr_t attr;	
	
	pthread_attr_init(&attr);
		
	pthread_create(&tid,&attr,threadFunc,NULL);

	sleep(1);
	
	pthread_attr_destroy(&attr);

	pthread_getattr_np(tid,&attr); //for stack sizes it must and shud otherwise the above function pthread_attr_getstack doesnt work. see this function copies all attributes of the specified thread into the attr object passed as second argument, by this attr we can get our required attribute details by invoking their respective function along-with(by passing) above filled attr object(wt we've got by invoking pthread_getattr_np) as argument..
	//here attr is an out param..

	print_stack_attr(attr);
	
	printf("The main thread is in paused state: press ctrl+c to come out of it\n");
	pause();
}

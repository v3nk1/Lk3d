//prog to print the changed default stack-attributes..
	//this must be static approach, is there any sence that if it dynamic(non senceful)..
		//Bcoz once default stack is allocated how you wil change the allocated stack at runtime..(foolish-ness)
		//So this alway must be static approach so before thread creation we must specify our attributes and then create a thread.

#define _GNU_SOURCE //used for pthread_getattr_np

#include<stdio.h>
#include<pthread.h>

#include<errno.h> //used for perror

#include<stdlib.h> //for malloc

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

void *stack_alloc(size_t size){

	static void *ptr ;
	ptr = malloc(size);//or use posix_memalign
	
	return ptr;

}


main(){
	
	pthread_t tid;
	static pthread_attr_t attr;	
	
	pthread_attr_init(&attr);

	size_t stacksize = 20*1024; //stack size must be >= 16*1024 bytes
	
	void *stackaddr = stack_alloc(stacksize);//stackaddr should point to the lowest addressable byte of a buffer of stacksize bytes that was allocated by the caller. not like clone() (in clone we are making it higher by adding stack_size)..
	
	if(errno = pthread_attr_setstack(&attr,stackaddr,stacksize)) perror("pthread_attr_setstack"); 
		
	if(errno = pthread_attr_setguardsize(&attr,10*1024)) perror("pthread_attr_setguardsize"); //it is ignored see d man page..
	
	pthread_create(&tid,&attr,threadFunc,NULL);

	sleep(1);
	
	pthread_attr_destroy(&attr);

	pthread_getattr_np(tid,&attr); //for stack sizes it must and shud otherwise the above function pthread_attr_getstack doesnt work. see this function copies all attributes of the specified thread into the attr object passed as second argument, by this attr we can get our required attribute details by invoking their respective function along-with(by passing) above filled attr object(wt we've got by invoking pthread_getattr_np) as argument..
	//here attr is an out param..

	print_stack_attr(attr);
	
	printf("The main thread is in paused state: press ctrl+c to come out of it\n");
	pause();
}

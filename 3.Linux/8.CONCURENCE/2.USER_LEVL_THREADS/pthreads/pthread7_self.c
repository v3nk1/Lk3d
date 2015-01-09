//to understand pthread_self function..

#include<stdio.h>
#include<pthread.h>

void *T(void *arg){

	printf("in thread: %lu\n",pthread_self());

	printf("tid of d thrd created by main :%lu\n",*(pthread_t *)arg);
}

main(){

	pthread_t tid;
	pthread_create(&tid,NULL,T,&tid);
	printf("in default thread: %lu\n",pthread_self());
	sleep(1);
	
}

/********************************************************************************************************************************
NOTES:
``````	In this program we are observing the behaviour of pthread_self function..
	
	If u use pthread_self() function in default thread(main()), then it returns tid of the calling thread(here main thread tidwill be returned..
	If u use in the threadFunction T then it returns the calling thread tid,here we are calling pthread_self in child thread so it returns child thread pid..
		To know is it returning the child thread tid or not we are checking as follows:
					I'm using the 4th argument of the pthread_create(), i passed the 4th argument as &tid,since bcoz i'm going to print the tid creatd by main thread (ie., nothing but child thread tid) in threadFunction T, i'm printing it to compare the pthread_self() returned tid in child thread, and pthread_create() function creatd tid are same or not?
	Obviously there are same...

********************************************************************************************************************************/


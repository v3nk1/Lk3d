//accessing global struct obj synchronizly using (pthread_join(),pthread_exit());

#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>

#define LOCK 1
#define UNLOCK 0

//pthread_t thread1,thread2;

int flag;

struct glob{

	int a;
	int b;
}o;

void *threadFunc1(void *arg){

	o.a=10;
	sleep(1);
	o.b=20;

	static int ret = UNLOCK; //static must and shud, otherwise garbage value..
	pthread_exit(&ret);
}

void *threadFunc2(void *thread1){  // here in thread1 we're having a pointer to pthread_t of thread1....
	
	void *get;
	pthread_join(*(pthread_t *)thread1,&get);
	printf("get= %d\n",*((int*)get));

	if(*(int *)get == UNLOCK){
		printf("member1 = %d\n",o.a);
		printf("member2 = %d\n",o.b);//u'll get updated data
		}

}

main(){

	pthread_t thread1,thread2;

	pthread_create(&thread1,NULL,threadFunc1,NULL);
//	sleep(5);
	pthread_create(&thread2,NULL,threadFunc2,&thread1); //we are passing the address of thread obj to void *thread1 in threadFunc2..

//	pthread_join(thread1,NULL);  it will cause the error since it already exited na?? gives garbage value for get..
	pthread_join(thread2,NULL);

	
exit(EXIT_SUCCESS);
}

//Accessing global struct obj by implenting poll locks shared library(shared object).. means we are providing an API
	/*(1)we are creating shared object for lock.c and provide it while compiling this file..
			cc -fPIC -c lock.c 
			cc -shared lock.o -o lib_lock.so                     */
	//(2) compilation: cc sync_tech5_0_plock_lib.c ./lib_lock.so -lpthread

#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>


struct glob{

	int a;
	int b;
}o;

void *threadFunc1(void *arg){

	lock();
	o.a=10;
	sleep(1);
	o.b=20;
	unlock();

}

void *threadFunc2(void *arg){

	lock();
	printf("member1 = %d\n",o.a);
	printf("member2 = %d\n",o.b);//u'll get updated data

	unlock();
}

main(){

	pthread_t thread1,thread2;
	
	pthread_create(&thread1,NULL,threadFunc1,NULL);
//	sleep(5);
	pthread_create(&thread2,NULL,threadFunc2,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	
exit(EXIT_SUCCESS);
}

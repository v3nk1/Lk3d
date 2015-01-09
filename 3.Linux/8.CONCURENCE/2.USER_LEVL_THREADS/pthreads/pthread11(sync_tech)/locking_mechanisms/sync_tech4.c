//In this prog we are trying to accessing global struct obj by 2 threads..

#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>

struct glob{

	int a;
	int b;
}o;

void *threadFunc1(void *arg){

	o.a=10;
	sleep(1);//if u dont give sleep it will execute in 1 shot, since simple 2 statements. what if thousands of instruction areplaced here.. so if 1000 is the case then in the middle of updation the cpu slice given to thread2 and it going to read half updated data na..? so to demonstrate 1000 member updation case i'm giving sleep(1) here, such that thread1 surely give a chance to thread2 (since thread1 will be suspended)..
	o.b=20;

}

void *threadFunc2(void *arg){

	printf("member1 = %d\n",o.a);
	printf("member2 = %d\n",o.b);//u'll get stalled(half updated and half not updated) data.

}

main(){

	pthread_t thread1,thread2;
	
	pthread_create(&thread1,NULL,threadFunc1,NULL);
	pthread_create(&thread2,NULL,threadFunc2,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	
exit(EXIT_SUCCESS);
}

/********************************************************************************************************************************
NOTE:
````` Now we are updating a structure object using thread1 and reading the updated values using thread2.
	
      case(i) : if schedular schedules thread1 first, then u will get output 10,0;
      case(ii): if schedular schedules thread2 first, then u will get output 0,0;

      run many times u will either get stalled data(half updated data) means one member is updated and other not (or) unupdated data 0,0. 

********************************************************************************************************************************/

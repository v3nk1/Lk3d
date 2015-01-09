#include<stdio.h>

#define LOCK 1
#define UNLOCK 0

int flag;

typedef unsigned int lock_t;

void lock(void){

	while(flag);

	flag = LOCK;

}


void unlock(void){

	while(flag == UNLOCK);	

	flag = UNLOCK;

}

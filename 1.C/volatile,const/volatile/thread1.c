/*
 * Compile with -O2 flag. 
 */

#include<stdio.h>
#include<pthread.h>

//volatile		//commnet or uncomment and check output
int a;

void *thread1(void *arg){
	printf("%s: Executed\n",__func__);
	while(!a){	//here for w/o volatile case !a will be replaced by 1(true) 
	//	printf("%s: a=%d, In odd loop\n",__func__,a); //Dont put any printf statements.
		}
	return NULL;
}

void *thread2(void *arg){
	
	printf("%s: Executed\n",__func__);
	a=1;
	return NULL;
}

main(){

	pthread_t tid1,tid2;
	
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);

	pthread_exit(NULL);
	
}

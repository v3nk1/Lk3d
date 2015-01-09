/*
 * Compile with -O2 flag. 
 */

#include<stdio.h>
#include<pthread.h>

volatile		//commnet or uncomment and check output
int a;

void *thread1(void *arg){
	printf("%s: executed\n",__func__);
	sleep(1);
	a=1;
	return NULL;
}

void *thread2(void *arg){
	printf("%s: executed\n",__func__);
	
	sleep(2);
	a=1;
	return NULL;
}

main(){

	pthread_t tid1,tid2;
	
	printf("%s: executed\n",__func__);
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);

	while(!a);		//without volatile it will be block forever,
				//since !a is replaced by 1(true);
				//After 3 seconds it automatically comes out of this loop. 
	printf("%s: Executed\n",__func__);
	
}

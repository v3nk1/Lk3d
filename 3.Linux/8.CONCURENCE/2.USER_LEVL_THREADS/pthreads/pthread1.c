//prog to know how to create a pthread using pthread_create function provided by possix library..

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *trd_Func(void *pas_val){

	printf("entered into child thread\n");
	printf("passed value from main-thread: %d\n",*(int *)pas_val);
	
}

main(){
	
	void *ret;

	pthread_t thread; //its an thread object(out-param), used to store the attributes of the thread..

	int pas_val=1234;

	pthread_create(&thread,NULL,trd_Func,&pas_val); //compile with cc tr_crte.c -lpthread or cc -pthread tr_crte.c
	
//	perror("pthread_create");	
//	sleep(10);
	pthread_join(thread,&ret);   //ret is an out-param, its used to read the exit state of the specified thread., or pass it as NULL;

		
	printf("main thread exited\n");
	exit(EXIT_SUCCESS);

}

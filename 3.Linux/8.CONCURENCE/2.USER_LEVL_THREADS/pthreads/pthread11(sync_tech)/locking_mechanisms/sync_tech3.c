//automic instructions..

#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>

int glob;

void *threadFunc(void *arg){

	int i;
	for(i=0;i<500000;i++) 
		//__sync_fetch_and_add (&glob,1); use any one of the automic instruction these 2 oprtns r same only return vals wil change, this return privious value, where as below one returns updated value..
		__sync_add_and_fetch (&glob,1);

}

main(){

	pthread_t thread1,thread2;
	
	pthread_create(&thread1,NULL,threadFunc,NULL);
	pthread_create(&thread2,NULL,threadFunc,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	printf("\nglob=%d\n\n",glob);
	
exit(EXIT_SUCCESS);
}

/*******************************************************************************************************************************
NOTES:
``````	This sychronisation problem occured only bcoz of we are incrementing a global data which is done by several instructions by compiler..
	What if we can update or increment a global data in 1 SHOT. ie., 1 single machine code will increaments the global data and stores updated value to back to glob..

	we can achive this by "AUTOMIC INSTRUCTIONS"..
	``````````````````````````````````````````````
		Every cpu will be supported some specified automic instructions provided for its archetecture..
		In this directory only there is a text file "Atomic.txt" check it out..
		In that i provide the automic instruction we can use heree clearly..
			or see man automic(dont use these man page atomic functions)

********************************************************************************************************************************/

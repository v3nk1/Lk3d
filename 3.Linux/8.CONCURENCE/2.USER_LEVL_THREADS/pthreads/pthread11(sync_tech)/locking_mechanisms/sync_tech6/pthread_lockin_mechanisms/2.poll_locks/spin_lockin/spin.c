//In this scenario 2 threads are accessing a same global data.. to avoid d reading of incosistent data i used here spin locks..

	//see the prog "vi ../../../../sync_tech1.c"

#include<stdio.h>
#include<pthread.h>

int glob;

pthread_spinlock_t spin;

void *threadFunc(void *arg){

	int i;
	pthread_spin_lock(&spin);
	for(i=0;i<800000;i++)
	glob++;
	pthread_spin_unlock(&spin);
	
}

main(){

	pthread_spin_init(&spin,0);

	pthread_t thread1,thread2;
	
	pthread_create(&thread1,NULL,threadFunc,NULL);
	pthread_create(&thread2,NULL,threadFunc,NULL);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	printf("glob=%d\n",glob); //glob value wont be persistance.

}

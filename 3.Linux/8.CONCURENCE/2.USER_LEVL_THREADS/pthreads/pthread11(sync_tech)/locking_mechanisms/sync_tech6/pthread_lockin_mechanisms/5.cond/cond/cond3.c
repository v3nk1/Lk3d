#include <stdio.h>
#include <pthread.h>
#include <signal.h>

int flag;

pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void *condsig(void *arg){

	printf("%s: Created\n",__func__);
	printf("%s: Doing critical job\n",__func__);
	//pthread_kill(*(pthread_t *)arg,SIGRTMAX);	//Spurious wakeup will happen

	/* Critical job */
	pthread_mutex_lock(&mutex);
	
	sleep(10);	

	printf("%s: Signaling..\n",__func__);
	flag=1;
	pthread_mutex_unlock(&mutex);

	pthread_cond_signal(&cond);

	return NULL;

}

void *condwait(void *arg){

	printf("%s: Created\n",__func__);
	printf("%s: Waiting for a signal\n",__func__);
	
	pthread_mutex_lock(&mutex);

	while(!flag){
		pthread_cond_wait(&cond,&mutex);
		}

	printf("%s: Got a signal\n",__func__);
	/* Do the dependent job */

	pthread_mutex_unlock(&mutex);

}

int main(){

	pthread_t tid1,tid2;
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&tid1,NULL,condwait,NULL);
	pthread_create(&tid2,NULL,condsig,&tid1);

	pthread_exit(NULL);
	
	return 0;
}

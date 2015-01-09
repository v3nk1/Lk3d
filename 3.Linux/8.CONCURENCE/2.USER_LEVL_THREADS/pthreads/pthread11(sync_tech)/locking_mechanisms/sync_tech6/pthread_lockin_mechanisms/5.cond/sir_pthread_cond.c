#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <malloc.h>		

#define EXIT_SUCCESS 0

char *start=NULL; /* Global data structure */

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int avail = 0;

static void * threadFunc1(void *arg)
{
	int ret, i = 0;
	char data=64;
	sleep(1);
	while(data<84) {
		pthread_mutex_lock(&mutex);
			data++;
			memset(start + i ,data,8);
			i+=8;
			start[i]='\0';
			printf("Produced data successfully \n");
			avail=1;
		pthread_mutex_unlock(&mutex);
		ret = pthread_cond_signal(&cond);         /* Wake sleeping consumer */
        	if (ret != 0)
            		perror( "pthread_cond_signal");
	}

	return NULL;
}

static void * threadFunc2(void *arg)
{
	int ret=0;
	while(1) {
		pthread_mutex_lock(&mutex);
			if(avail==0) {
				printf("Wait for data \n");	
				ret = pthread_cond_wait(&cond, &mutex);
                	        if (ret != 0)
                	                perror( "pthread_cond_wait");
			}
        		printf("%s\n",start);
			printf("Consumed data successfully\n");
			avail=0;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int ret;

    start = (char *)malloc(4096);	

    ret = pthread_create(&t1, NULL, threadFunc1, NULL);
    if (ret != 0)
        perror("Pthread Create :   ");

    ret = pthread_create(&t2, NULL, threadFunc2, NULL);
    if (ret != 0)
	perror("Pthread Create:    ");

    ret = pthread_join(t1, NULL);
    if (ret != 0)
	perror("Pthread Join:     ");

    ret = pthread_join(t2, NULL);
    if (ret != 0)
	perror("Pthreaf Join :    ");

    exit(EXIT_SUCCESS);
}

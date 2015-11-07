/* thread_incr_mutex.c

   This program employs two POSIX threads that increment the same global
   variable,using mutexes . As a consequence,updates are not lost.

*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *                   /* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg)
{
    int local,j,ret;
    int loops = *((int *) arg);
	printf("\n %s: \n",__func__);
    for (j = 0; j < loops; j++) {
	ret = pthread_mutex_lock(&mtx);
//	ret = pthread_mutex_lock(&mtx);
        local =  glob;
        local++;
        glob = local;
	sleep(10);
	ret =  pthread_mutex_unlock(&mtx);
    }

    return NULL;
}
void *Func2(void *arg) 
{

	int ret;
	sleep(2);
 	ret = pthread_mutex_unlock(&mtx);
	printf("ret %d\n", ret);
	while(1);
	return NULL;
}

int main()
{
    pthread_t t1, t2;
    int loops=10000000, ret;

    ret = pthread_create(&t1, NULL, threadFunc, &loops);
    if (ret != 0)
        perror("Pthread Create :   ");

    ret = pthread_create(&t2, NULL, Func2, &loops);
    if (ret != 0)
	perror("Pthread Create:    ");

    ret = pthread_join(t1, NULL);
    if (ret != 0)
	perror("Pthread Join:     ");

    ret = pthread_join(t2, NULL);
    if (ret != 0)
	perror("Pthreaf Join :    ");

    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}

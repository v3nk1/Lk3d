#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0;

static void *                   /* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg)
{
    int local,j;
    int loops = *((int *) arg);
	printf("\n %s: \n",__func__);
    for (j = 0; j < loops; j++) {
        local = glob;
        local++;
        glob = local;
    }

    return NULL;
}

int
main()
{
    pthread_t t1, t2;
    int loops=10000000, ret;

    ret = pthread_create(&t1, NULL, threadFunc, &loops);
    if (ret != 0)
        perror("Pthread Create :   ");

    ret = pthread_create(&t2, NULL, threadFunc, &loops);
    if (ret != 0)
	perror("Pthread Create:    ");

    ret = pthread_join(t1, NULL);
    if (ret != 0)
	perror("Pthread Join:     ");

    ret = pthread_join(t2, NULL);
    if (ret != 0)
	perror("Pthreaf Join :    ");

    printf("glob = %d\n", glob);
    return 0;
}

//Here we are trying to set the scope of the thread from SYSTEM TO PROCESS using "pthread_attr_setscope()"..
//& IN THIS I'M USING PERROR() WHICH IS NOT SUPPORT FOR PTHREADS,BUT I MAKE IT SUPPORTED BY SETTING ERRORNO AS MY SELF.
//ACTUALLY PERROR() DOESNT SUPPORT BCOZ PTHREADS DOESNT SET ANY ERRNO AS PREVIOUS FUNCTIONS(FORK(),CLONE()..) SET.

#include<stdio.h>
#include<pthread.h>

#include<errno.h>

void *threadFunc(void *arg){

	printf("child thread is created\n");

}


main(){

	pthread_t tid;

	pthread_attr_t attr;

/*I'M USING HERE PTHREAD() FUNCTION BY SETTING ERRNO AS FOLLOWS, SINCE PTHREADS DOESNOT SET ERROR NUM(that why perror doesnt wrk)*/	
	if(errno = pthread_attr_setscope(&attr,PTHREAD_SCOPE_PROCESS)) perror("pthread_attr_setscope");

	pthread_create(&tid,&attr,threadFunc,NULL);


}


/********************************************************************************************************************************
	In linux we cannot change the scope of the thread..
	by default it will be PTHREAD_SCOPE_SYSTEM only..

*********************************************************************************************************************************/

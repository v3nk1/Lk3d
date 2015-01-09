/*
 * We can do this notification in 2 ways, using sigaction() and using sigprocmask().
	1. Using sigprocmask()
		gcc sigque.c -D PROCMASK
	2. Using sigaction()
		gcc sigque.c

 * Without these 2 even though process has been blocked by sleep() or getchar()
   after signal asserstion default handler will be invoked means automatic termination for
   realtime signals.
 */


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<strings.h>

#ifndef PROCMASK
void handler(int no,siginfo_t *info,void *arg){

	printf("Got data ptr: %p -> %s\n",info->si_value.sival_ptr,(char *)info->si_value.sival_ptr);

}
#endif

pid_t pid,cpid;

main(){

	pid=getpid();
	switch(fork()){

		case 0:
			{
			/*static*/ int a=1234;
			static 
			char buf[20]="what is it?";
//			scanf("%s",buf);
//			printf("Scanned: %s\n",buf);
			union sigval val;
			val.sival_ptr=
					//&a;
					//"This is a testing prog";
					buf;
//			printf("&a: %p\n",&a);
//			val.sival_int=a;
			cpid=getpid();
			sleep(1);
			sigqueue(pid,SIGRTMIN,val);
			}
			break;
		default:
			{
			siginfo_t info;
			sigset_t set;
			sigemptyset(&set);
			sigaddset(&set,SIGRTMIN);

#ifdef PROCMASK
			sigprocmask(SIG_BLOCK|SIG_SETMASK,&set,NULL);	/*OR*/
#else
			struct sigaction act;
			bzero(&act,sizeof(act));
			act.sa_sigaction=handler;
			act.sa_flags=SA_SIGINFO;
			sigaction(SIGRTMIN,&act,NULL);
#endif
			sigwaitinfo(&set,&info);
				/* See man sigwaitinfo() to know why using sigprocmask() here */

//			printf("Got data ptr: %p -> %d\n",info.si_value.sival_ptr,*(int *)info.si_value.sival_ptr);
			printf("Got data ptr: %p -> %s\n",info.si_value.sival_ptr,(char *)info.si_value.sival_ptr);
//			printf("Got val: %d\n",info.si_value.sival_int);
			}
			break;
		}
}

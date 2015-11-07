#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

#define CHILD 0

pid_t cpid, cpid1, cpid2;

/* signal handler to handle SIGCHLD event */
void sighand(int signum)
{
	printf("%s: I am in sig handler\n",__func__);
	wait(NULL);
	/* wait()
	   {
	   step 1: block caller until child terminates
	   step 2: instruct kernel's process manager to destroy defunc child
	   step 3: return child's exit status to caller
	   } */
}

int main()
{
	printf("I'm in main pid: %d\n",getpid());
	cpid = fork();
	if (cpid == CHILD) {
		printf("%s: I am first child pid: %d, ppid: %d\n", __func__,
			       getpid(),getppid());
		signal(SIGCHLD, sighand);
		cpid1 = fork();
		if (cpid1 == CHILD) {

			printf("%s: I am child1 pid: %d, ppid: %d\n", __func__,
			       getpid(),getppid());
			/*
			 * Forcebly terminating child with exit() and kept alive parent with getchar() 
			 * such that we can see the <defunc> state of child until parent terminated.
			 */
			exit(2);	
		}

		else {
			//sleep(1);
			cpid2 = fork();
			if (cpid2 == CHILD) {
				printf("%s: I am child2 pid: %d, ppid: %d\n", __func__,
				getpid(),getppid());
			/*
			 * Forcebly terminating child with exit() and kept alive parent with getchar() 
			 * such that we can see the <defunc> state of child until parent terminated.
			 */
				exit(3);
				}
			else{
				printf("waiting for getchar() %d:%d\n",getpid(),getppid());
				getchar();
			//	exit(4);
				}
			}
	
	/*
	 * Here the main parent is waiting for synchronous cleanup. Increase the sleep 
	 * that much more seconds will wait.
	 */
	printf("Process pid: %d having ppid: %d Sleeping for 20 sec\n",getpid(),getppid());
	sleep(20);

	} 
	else {
		wait(NULL);
		getchar();
	}
	return 0;
}

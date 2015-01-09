//Is global data is accessble in child thread, it can update the global data?

#define _GNU_SOURCE

#include<stdio.h>
#include<sched.h>
#include<stdlib.h>

#define STACK_SIZE 12000

int glob; //BSS SEGMENT

void check_err(int ret){

	if(ret == -1) perror("clone");
	else return;
	
}

int threadFunc(void *arg){

	printf("created a child(clone) process\n");
	glob = 10000;
	
	printf("in child glob= %d\n",glob); // so after 10sec it prints the updated value. since unlike fork, child here updates the data becoz of sharing.
	printf("update of glob is done in child thread\n");

}

int main(){

	glob = 10;
	printf("In parent process\n");
	printf("before child glob= %d\n\n\n",glob);

	void *child_stack = malloc(STACK_SIZE);

	int ret = clone(threadFunc, child_stack+STACK_SIZE ,CLONE_FILES|CLONE_VM ,NULL);
	
	check_err(ret);

	printf("parent went to sleep for 10sec\n");
	sleep(10); /*	it makes the parent suspend for 10sec, so the schedular can schedule cpu usage(givin cpu slice) to any other process. here case child has taken that.
			minimum give 10sec sleep, i'm not sure that it may enough or may need more time to execute child thread. since we dont know that when will schedular schedule this child process. i guess it was 10,but i'm not sure..
			Here in this case if u dont gv sleep(10), so u r not giving enough time to execute child.. before the child execution parent terminates. here i'm assuming that child will comes to context by 10 sec.
	*/   


	// Or use\
	waitpid(-1,NULL,__WALL);


	printf("after child glob= %d\n",glob); // so after 10sec it prints the updated value. since unlike fork, child here updates the data becoz of sharing.

	return 0;

}

/*****************************************************************************************************************
NOTES:
``````	Update of glob is done only if and only if u pass CLONE_VM flag(this flag is ment for sharing). 
	
	Other wise it also like fork() ie., copy-on-write happens, means both will maitain their own resouces if any write happens	    in fork()  at starting of child data sharing(ie., above fork data will be shared) will be there untill u write any thing in child/parent after fork().

*****************************************************************************************************************/

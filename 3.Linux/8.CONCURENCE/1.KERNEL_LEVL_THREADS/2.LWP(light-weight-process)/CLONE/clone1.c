//how to create a child(LWP) using clone();

#define _GNU_SOURCE

#include<stdio.h>
#include<sched.h>
#include<stdlib.h>

#define STACK_SIZE 12000    // the stacksize allocated for child-thread(process) must be greater than 16kb. so min=16K, max=2M.

void check_err(int ret){

	if(ret == -1) perror("clone");
	else return;
	
}

int threadFunc(void *arg){

	printf("created a child process\n");
//	getchar();  // if u press enter then the child goes into ZOMBIE STATE. there is only option to see child in "ps -Af".
}

int main(){

	void *child_stack = malloc(STACK_SIZE);

	int ret = clone(threadFunc, child_stack+STACK_SIZE ,CLONE_FILES|CLONE_VM ,NULL);/*without additon of STACK_SIZE to allocated child_stack segmentation fault.

		Becoz malloc is heap_segment, (except stack all segments hv same behaviour as heap)in heap the address grows from lower to higher, apart of that stack grows from higher to lower address.

		And malloc returns starting adress(ie., lower address) of allocated frame(Block).

		But through clone we are giving the stack starting address for child process, but the problem is stack grows frow higher to lower so we must pass the ending address of allocated mem block, so we are adding STACK_SIZE to it.

*/
	
	check_err(ret);
	
	printf("In parent process\n");

	while(1);// Or to wait parent until child terminate use below \
	waitpid(-1,NULL,__WALL);	

	return 0;

}


/*****************************************************************************************************************
NOTES:
``````
	CLONE_FILES|CLONE_VM those flags are for sharing purpose, you'll aware of them by comming sessions.

*****************************************************************************************************************/

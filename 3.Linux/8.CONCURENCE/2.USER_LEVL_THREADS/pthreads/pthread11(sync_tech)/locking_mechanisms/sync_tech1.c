//In this scenario 2 threads are accessing a same global data.. whats going to happen??

#include<stdio.h>
#include<pthread.h>

int glob;

void *threadFunc(void *arg){

	int i;
	for(i=0;i<800000;i++)
	glob++;

}

main(){

	pthread_t thread1,thread2;
	
	pthread_create(&thread1,NULL,threadFunc,NULL);
	pthread_create(&thread2,NULL,threadFunc,NULL);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	printf("glob=%d\n",glob); //glob value wont be persistance.

}


/*********************************************************************************************************************************
NOTES:
``````	In this we get incosistent(not constant) data while u run this program sevaral times. the reason behind this is the thread creation is in our hand, but when they will execute is not in our hand.. its purely depends on schedular.
	So thread1 is created by invoking pthread_create, then it will be placed in the run que, when ever cpu gets free thread1 will hav a cpu slice and executes..
	So we are creating 2 threads like that from default thread(main)

	And those 2 threads are trying to access same global data..
	And as part of thread function we are updating the global data by using increment operation.. glob++;
	
	if u run this for sevaral time you'll not get the persistant(constant) data..
	
	
=====>	Its becoz of glob++;
	For it glob++ is seems like 1 instruction..
	For compiler its like 4 instuctions(in assemble(machine) code)		||	(in C):
			{							||	{
			 fetching from memory(RAM) to registers;          	||	int local_var;
			 store it in a local variable;				||	local_var = glob_var data;
			 add local var to 1					||	local_var = local_var+1;
			 storing back updated local var to local var		||	
			 updating global data;					||	glob_var = local_var;
			}							||	}
	
	If thread1 is in execution say its in middle of those above steps, its cpu slice is over, and thread2 hav cpu slice now.
    so thread1 is even not updating the value, but thread 2 started execution it also un-updated global data.
	(say thread2 has incremented global variable un-interreptedly):
			so now global data is updated from 0 to 1 by thread2 and now its slice is over..
	so CPU control given to thread1 again, so it starts exectution where it stops and it also again updates the global data to 1(becoz it also reads global data as 0 in previous execution of thread1).
	
********| See dont think that it will execute half of the loops in above case(ie., dont think that globe value will be 800000 at last) we dont know how those threads are executed and scheduled..
	say thread1 started and in the middle cpu slice is given to thread2, say thread2 executes 2 times repeatedly so thread 2 updates global value from 0 to 2.. and thread1 again get cpu slice and it resumes where it stops so it executes 1 time NOW THREAD1 WILL UPDATE GLOBE VALUE TO 1(SINCE IT HAV DATA OF GLOBE AS ZERO(SINCE IT RESUMES WHERE IT PRIVIOUSLY STOPPED)).

	THATS WHY IT WOULDN'T BE PERSISTANT..

********************************************************************************************************************************/

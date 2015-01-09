//accessing global struct obj if and only if its in UNLOCK state using poll locks concept..

#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>

#define LOCK 1
#define UNLOCK 0
#define UPDATE 10

int flag;  //used to set d lock/unlock..

struct glob{

	int a;
	int b;
}o;

void *threadFunc1(void *arg){

	while(flag) printf("lockd by thrd2\n");   //it fails if flag == UNLOCK , and then only the bellow code will executes..

	flag = LOCK;
	
	o.a=10;
	sleep(1);    //assume that the objects are (huge)1000 of assignments(to be updated values).
	o.b=20;
	
	flag = UNLOCK;

}

void *threadFunc2(void *arg){

	while(flag) printf("lockd by thrd1\n");
	
	flag = LOCK;

	printf("member1 = %d\n",o.a);
	printf("member2 = %d\n",o.b);//u'll get updated data

	flag = UNLOCK;

}

main(){

	pthread_t thread1,thread2;
	
	pthread_create(&thread1,NULL,threadFunc1,NULL);
//	sleep(5);
	pthread_create(&thread2,NULL,threadFunc2,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	
exit(EXIT_SUCCESS);
}


/********************************************************************************************************************************
NOTES:
``````	POLL-LOCKs:
	``````````` These are used for locking the access of a object if some is reading/updating that object. If no one update/operate on that data that object will be unlocked state, so anyone can go and access that data..
	
		Here in this scenario also same as previous scenario thread1 is updating and thread2 is reading those values.
		But here thread2 will block untill thread1 completes its update by using poll locks concept..
	
	======>	In this we are using a variable of type int named as "flag" which must be declared as GLOBAL. Using that we are 		giving a state(LOCK/UNLOCK) for reading & for updating..

	======> Initially flag state is zero since it is a global variable of type int. so any thread can access it. once a thread		(thread1/thread2) starts doing some operations with global object then flag is set to lock(1) such that no one cannt 		  access it.
	
	======>	lets say if thread1 is doing operations with global object then the flag state is set to 1(LOCK).Its cpu slice is 		over in the middle of execution.
		If u read directly in thread2, u will read those half updated values but to get updated data we put a condition 		like "go and read the data if and only if flag is 0(UNLOCK)"; but thread1 make it as 1(LOCK), now thread2 unable to 		  read the gobal data since the flag = 1.

	======>	Again cpu slice is given to thread1, After completion of its updation thread1 will set that flag to 0(unlock);

	======>	If thread2 reading the data from global object then if its time slot is over then what happens?? so thread1 will 		update values even thread2 not red(read) completely.. so its also become a problem..!
			to avoid this put a conditon for flag in thread2 also such that once it(thread2) enter into reading of 			global data the flag will set to LOCK(1); once it completes reading set that flag to UNLOCK(0) so that any one can 		  access now..


	DRAWBACKS: (cpu slice wasting)
	``````````  The main drawback or disadvantage of poll locks is even thread2/thread1 gets a cpu slice its being blocked in  		   while until the flag chaged to UNLOCK(0). So its wasting cpu-slice.

	=======> To avoid this we use wait-locks(semaphores).

********************************************************************************************************************************/


//TO UNDERSTAND THESE CONCEPTS PLEASE COME ACROSS THE PREVIOUS SESSIONS OF SYNCHRONIZATION CONCEPTS..(FROM STARTING of "sync_tech" directory)

See in semaphores: It is mandatory to intialise simaphore by using "sem_init" function provided by semphore.h library..
`````````````````` See man semaphore.h

=====>	Dont blindly fix that if u create an instance of sem_t automatically it will initialise..

		1) See this is what happens if u create the instace of sem_t object locally then there will be some garbage value..		   since the initial state of the local variable is garbage value naa??

		So if u make a call to sem_wait it will work but since inital value is not zero na?? means it in unlock state.. 		   (any value >0 is considered as unlocked state in semaphores)..
		 
		You can print the semaphore value(here garbage value) by "sem_getvalue()"(by creating an instance of int and pass 		   its address as 2nd argument(2nd arg is an outparam));


		2) If u declared sem_t object as global then its semaphore val is zero(locked state) since any global object(data) 		   initial state is zero.. so this locked state of a binary semaphore..
			but in the threadfunctoin if u r perform a sem_wait() then it will be cause a blocking the process(thread) 			forever..
			its becoz u r trying to lock a semphore which was already locked..so it will wait until it unlock and then 			it again locks that.(that is the default behaviour of semaphore)
		

	So to avoid these undefined behaviours it is mandatory to initialize a semphore by a function sem_init(&sem,0,1);
			the 3rd argument shud be >0 (in any semaphore) otherwise: if u pass 0 then similar to 2) point
										  if u pass <0 then undefined behaviour, since semphores value shuld not be less than 0; that the semaphore implementation standard.

=====>	For each and every global object there shuld be one sem_t obj..
	scenario1:
	``````````
		there is one global data; 2 threads are accessing it simultaneously..
		what if in each of two threadFunc's i created sem_t instance locally and initialized by using "sem_init"..
		
		In the each threadFunc i locked before operations and unlocks after operations completed; then again inconsistent data will result, means if u run ./a.out the output is not constant(again we comes to first problem).. to understand this see the program named as "sem_errors.c" in this directory..

		To avoid this just declare sem_t object globally.. and initialize it in the main thread..


ADVANTAGE OF WAITLOCKS IS: THESE DOESNT WASTE ANY CPU SLICE.. BUT POLL LOCKS WASTES CPU SLICE EVEN THE SCHEDULER GIVEN CPU SLICE  `````````````````````````` TO IT.

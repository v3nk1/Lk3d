/* Write a prog which will create 2 user level threads T1 and T2, 
		T2 shud synchronize with T1 and collects its(T1) exit status.
		T1 take a string as argument and returns its length as exit state.

*/

//APPROACH 1:(create thread_t objects globally) since we are using thread1 in T2; 

#include<stdio.h>
#include<pthread.h>

#include<string.h>
#include<stdlib.h>

pthread_t thread1,thread2;  

void *T1(void *str){

	printf("thread1 created\nwaiting at getchar()\n");
	getchar();
		
	static int ret; //WE MUST DECLARE IT AS STATIC, since we are using ret out of this block. 
	ret= strlen((char *)str);
	//printf("len%p",&ret);
	pthread_exit(&ret);

}

void *T2(void *arg){
	
	printf("thread 2 is created\n");
	sleep(1);
	void *len;

	pthread_join(thread1,&len);

	printf("len returnd by T1 is: %d\n",*(int *)len);

}

main(){

	//pthread_t thread1,thread2;
	
	pthread_create (&thread1,NULL,T1,"VENKATESH");
	//pthread_create (&thread2,NULL,T2,&thread1);
	pthread_create (&thread2,NULL,T2,NULL);

//	pthread_join(thread1,NULL);    /*DONT OPEN IT, CAUSES GAURBAGE VALUE IN LENGTH*/ becoz its already terminated(exited)..
	pthread_join(thread2,NULL);
}


/****************************************************************************************************************
NOTES:
`````` 
STATIC:
``````` Static has scope: block scope; and life time: entire program. 
                   ```````````````````     ``````````````````````````   SEE VECTOR METIRIAL.
        Means when the static variable is declared it allocates memory.. compiler distroys that memory only when the program terminates. So the updated value is stored in static variable like as global variable, but in global variable any file can access it by extern keyword, where as static has no such access(so has security).

=====>  but when u dealing with static, the variable name is not accessible throughout the program(ie., name is local to block);
        so deal with addresses..


*******************************************************************************************************************/


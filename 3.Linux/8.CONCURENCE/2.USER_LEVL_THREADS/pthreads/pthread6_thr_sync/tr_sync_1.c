/* Write a prog which will create 2 user level threads T1 and T2, 
		T2 shud synchronize with T1 and collects its(T1) exit status.
		T1 take a string as argument and returns its length as exit state.

*/

//In this apprach we are sending thread1 obj to T2 through pthread_create..

#include<stdio.h>
#include<pthread.h>

#include<string.h>
#include<stdlib.h>
#include<errno.h>

void *T1(void *str){

	printf("thread1 created\n");
	
	static int ret;    //WE MUST DECLARE IT AS STATIC, since we are using ret out of this block.
	ret= strlen((char *)str);
	//printf("len%p",&ret);
	pthread_exit(&ret);

}

void *T2(void *arg){  //HERE WE ARE CATCHING "&thread1 OBJECT" TO "void ptr 'arg'" WHAT WE'VE PASSED DOWN..******************
	
	printf("thread 2 is created\n");
	sleep(1);
	void *len;
	if(errno=pthread_join(*(pthread_t *)arg,&len))
		perror("pthread_join");
	//pthread_join(thread1,&len);perror("pthread_join");   it throws an error that thread1 not declared.

	printf("len returnd by T1 is: %d\n",*(int *)len);
}

main(){

	pthread_t thread1,thread2;
	
	pthread_create (&thread1,NULL,T1,"VENKATESH");
	pthread_create (&thread2,NULL,T2,&thread1);  
		//here i intellegently passed address of thread1 object.. ******************


//	pthread_join(thread1,NULL);  /*DNT OPEN IT, IT CAUSES GAURBAGE VALUE IN LENGTH VARIABLE*/ Bcoz it already exited..
	pthread_join(thread2,NULL);
}


/*****************************************************************************************************************
NOTES:
`````` 
STATIC:
```````	Static has scope: block scope; and life time: entire program. 
		   ```````````````````	   ``````````````````````````   SEE VECTOR METIRIAL.
	Means when the static variable is declared it allocates memory.. compiler distroys that memory only when the program terminates. So the updated value is stored in static variable like as global variable, but in global variable any file can access it by extern keyword, where as static has no such access(so has security).

=====>	but when u dealing with static, the variable name is not accessible throughout the program(ie., name is local to block);
	so deal with addresses..


*****************************************************************************************************************/

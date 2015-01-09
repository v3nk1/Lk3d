
1st of all make a point clear that pthreads are not showd by "ps -Af" or "ps -el". Since it is RUN IN USER SPACE(user level theads). ps -el/-Af can show the processes run in kernel space only..


See for pthreads it is mandatory to check whether that particular function is SUCCESS or FAILED..

	how can u check that....??
	
	 YOU CANNOT CHECK IT BY PERROR():
	 --------------------------------
		Untill this Userlevel threads, u came across checking the API successed or failed by using a predifined function called "perror()" provided by stdlib.h library.. I think you started d usage this perror() from FILES.. right?? 

		How perror() API works: 
				If u used fuction like clone() or fork() or read(), write(), lseek(), open(), close() all these are worked with perror(); becoz those fuctions u see before pthread, has a behaviour like this:
				if the function fails/success then it(fuction) update/pass/set a value(errno) to stderr(its fd=2).. such that when u invoke perror it goes and read the error value and prints the appropriate mesg..
				std input  = fd(0)
				std output = fd(1)
				std error  = fd(2)
			these three are default file descriptors..
		if u open a file then u will get its fd as (3), Bcoz 0,1,2 are already in used..

	SO THE PROBLEM HERE IN PTHREAD IS THREADS WONT SET ANY ERROR VALUE.. THATS WHY PERROR ALWAYS PRINTS SUCCESS(even if the particular function failed)..

	TO KNOW THE SUCCESS/FAILURE:
	----------------------------
		Just check the fuction return values by if/switch kind of control structures..
		My suggistion is just put the entire pthread_function in a if condition braces and make the condition exectute if and only if the particular function fails(its achieved by put a not to that like !pthread_fuction()); it also checking return value and invoked.. (write the condition by seeing the return values in the man page of that particular pthread_func).
		In most of the pthread_functions return 0 in success..

							some error macro on failure..

OR U CAN USE PERROR BY SETTING errno:
-------------------------------------
	Take the return value of every funtion and store it a integer variable. as like bellow:
	
	ex:
	```	#include <errno.h>
		#include <stdlib.h>
	
		int err_ret;
	
		err_ret = pthread_detach(-----------);
		
		if(err_ret != 0){
				
				errno = err_ret;
				perror("pthread_detach");
				exit(10); //use random numbers as argument of exit, such that in large prog if any error occured u can found it by "$?" in shell prompt, then it will display the exit num what u hav given in program..
				
			}


	Or u can write a function for this and invoke it like perror() where u want....
		see man 3 pthread_getattr_np: In that he define a fuction like macro (line:107); In that program so much matter is there see it carefully..

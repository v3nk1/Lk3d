// Compile with -O2 -S -m32 flags and then see test.s, with volatile/ without volatile
			//1. with volatile every time while loop iterating it takes the value form
			// from the location.
			//2. without volatile it checks only at the time of first iteration only.
			
#include<stdio.h>

//volatile 
int some_int = 100;

main(){
while(some_int == 100)
{
   //your code
}

}

#include<stdio.h>

/*static*/ void xyz(void){  //comment and uncomment it and see results..

	printf("accessable by exetern keyword if no static prefixed\n");

}



/*
NOTE: Compile it like "cc stat1.c stat2.c"
	      and run "./a.out"
		
				if static is commented then works fine;
				not comments it creats security for that function such that no one cannt access it out of this file.


*/

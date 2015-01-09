#include<stdio.h>
#include<stdlib.h>

main(){

	int i;

	srand(getpid()); //if srand() is feeded with a constant number then sequence generated also same for every time.
			// to change that behaviour we are giving getpid() as argument bcoz it will change every time u execute.

	for(i=0;i<10;i++) printf("%03d ",rand()%100);
	//for(i=0;i<10;i++) printf("%3d ",rand()%100+1);
	//for(i=0;i<10;i++) printf("%d ",rand()%100+1);

	printf("\n");
}

/*************************************************************************************************
NOTES:
``````1) Here in rand() it will generate a unsigned num of unsigned integer range. So to make them as required range we are doing  modulo division of rand() with RANGE. In above example i want a 10 random num in range 0-7(min=0, max=7).
		
		for(i=0;i<10;i++) printf("%03d ",rand()%7); //here if u modular div by 7 then the remainder must be between 0-7 								na?? that how it will work..

      2) If u want to exclude 0 from the above generated set of numbers then add 1 to the "rand()%10".
		
		for(i=0;i<10;i++) printf("%03d ",rand()%7+1);  so here range (min=1 , max=7)
	

**************************************************************************************************/

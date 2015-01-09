#include<stdio.h>

main(){

	int x = 10;
//	int y = 10;
	int p;
	int q;

	printf("%d %d %d\n",x,x++,x++);
		/*
		 * Here the concept is 1st preferece to x++ and ++x and then x strating from right to left
		 * x++ will return instantly(immediately) while ++x and x will return after end of all sequence				* (ie., ++x & x these returns updated value only)
		 * 3rd x++ will return 10 and updated x to 11, 2nd x++ will return 11 and updated x to 12, at last 3rd 			* returns 12
		 * 12 11 10
		 */	
	x=10;
	printf("%d %d %d\n",x,++x,++x);
		/*
		 * Here the concept is 1st preferece to x++ and ++x and then x strating from right to left
		 * Here no x++, so ++x will not return immediately
		 * ++x updated x to 11, 2nd ++x 12
		 * so output: 12 12 12
		 */	

	x=10;
	printf("%d %d %d\n",x,x++,++x);
		/*
		 * Here the concept is 1st preferece to x++ and ++x and then x strating from right to left
		 * x++ will return instantly while ++x and x will return after end of all sequence
		 * 3rd ++x updated x to 11, 2nd x++ will return 11 and updated x to 12, at last 3rd 12
		 * o/p: 12 11 12
		 */	

	x=10;
	printf("%d %d %d\n",x,++x,x++);
		/*
		 * Here the concept is 1st preferece to x++ and ++x and then x strating from right to left
		 * x++ will return instantly while ++x and x will return after end of all sequence
		 * 3nd x++ will return 10 and updated x to 11, 2nd ++x updated x to 12, 3rd returns updated x.
		 * o/p: 12 12 10
		 */	
		

}

/*

12 11 10
12 12 12
12 11 12
12 12 10

*/

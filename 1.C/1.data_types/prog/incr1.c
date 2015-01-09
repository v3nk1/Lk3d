#include<stdio.h>

main(){

	int x = 10;
//	int y = 10;


//	   >>------------->
//	x = ++x + ++x + ++x ;
	/*
	 * Here above case ++ has highest precedence than + so according to associativity(Left to right)
	 * 1st ++x executes then x=11, then 2nd ++x executes then x=12;
	 * then it adds x+x = 12+12 =24;
	 * then 3rd ++x executes then x=13 & add this also to 24
	 * So x = 12+12+13 = 37; see assembly code, by compiling with -S flag..
	 */


//	x=10;
//	    -------------------------->	
//	x = ++x + ++x + ++x + x++ + x++;
		/*
		 * Here as above: 12+12+13+13+14 = 64;
		 */


//	x=10;
//	x = x++ + ++x + ++x;
//	    -------------->
		/*
		 * Here the x value 1st 10 and returned 10 for computing, and updated to 11
		 * now ++x is 12 returned for computation, updated x to 12
		 * again ++x is 13 returned for computaion updated x to 13
		 * Then so result 10+12+13 = 35.
		 */
	

//	x=10;
	x = ++x + x++ + ++x;
		/*
		 *
		 */
		

	
	printf("x= %d\n",x);

//	y++ + printf("%d============>\n",y);
		/*
		 * Here y value is not incremented in printf, it will increment in ", or ;" seperated statements only
		 * So conclusion of above statement is + isnt a statement completion
		 */
	
/*	y=10;
	y++,printf("%d============>\n",y);
	y=10;
	y++;printf("%d============>\n",y);

	y=10;
	y = y++ + y++ + y++ + y++;
*/
	/*
         * Here above case ++ has highest precedence than + so according to associativity 
         * 1st y++ executes then y=10(returns for calculation) after returned then +
	 * 2nd y++ executes then y=10(returns for calculation) after returned then +
	 * 3rd y++ executes then y=10(returns for calculation) after returned then +
	 * 4th y++ executes then y=10(returns for calculation) after returned then 
	 * so y= 40 
	 * then four 1's{since we have four addtions on y} are added reapeatedly (see assembly code of this programme)
         * as y=y + 1+1+1+1 = 44;
         */
	

//	printf("x= %d\ny= %d\n",x,y);
//	printf("y= %d\n",y);

}

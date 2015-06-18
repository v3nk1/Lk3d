//Bcoz of comparision b/w singed and unsigned it implicitly converts signed to unsigned and then compare

#include<stdio.h>

main(){

	unsigned u=10;
	signed s=-1;

	//if(-1<10)
	//if(-1<u)
	if(s<10)
//	if(s<u)	//if(u>s)
		printf("u is big\n");
	else 
		printf("s is big\n");
	
}

	/*
	 * If give integer constant or bare integer like 10,20 in the conditions
	   then it will be treated as (signed long) constant. If both are signed
	   then result is determenstic. if not implicit typecast takes place.
	 */


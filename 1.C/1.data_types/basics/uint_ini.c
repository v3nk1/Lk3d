//Bcoz of comparision b/w singed and unsigned it implicitly converts signed to unsigned and then compare

#include<stdio.h>

main(){

	unsigned u=10;
	signed s=-1;

	if(s<u)	//if(u>s)
		printf("u is big\n");
	else 
		printf("s is big\n");
	
}

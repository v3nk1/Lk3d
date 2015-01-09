//Here this function like macro which has a,b will be joined(concate) together and replaced in the place of concate(2,3)

#include<stdio.h>

#define concate(a,b) 	`a##b`

main(){

	char *tmp;
	tmp = concate(2,3);
	printf("%d\n",tmp);

}

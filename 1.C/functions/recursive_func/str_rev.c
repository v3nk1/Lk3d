#include<stdio.h>

char *str_rev(char *str){

	if(*(str+1))//to neglect '\0' to print in stdout
		str_rev(str+1);

	printf("%c",*str);
	
}

main(){

	str_rev("Hello");
	printf("\n");

}

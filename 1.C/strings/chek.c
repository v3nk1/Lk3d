#include<stdio.h>
#include<string.h>

main(){

	char s[]="this",*ptr=s;
	printf("%c %c\n",*s,*s++); //here *s is valid coz its points base addres, bt *s++ not valid becoz its not a ptr to increment by type size.
	printf("%c %c\n",*ptr,*(++ptr)); // here ptr inc nd dec operations are valid

}

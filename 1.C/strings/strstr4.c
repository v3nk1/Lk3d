//searching for a string in a given string


#include<stdio.h>

char *func(char *str,char *sub){
	
	int len = strlen(sub);
	char ch;

	while(*str){
		ch = str[len];
		if(strcmp(str,sub) == ch)
					break;
		//printf("%s = %s\n",str,sub);
		//printf("strcmp: %d\n",strcmp(str,sub));
		str++;
	}
	if(*str)
		return str;
	else return NULL;
}


main(){

	char *p = func("venkatesh","enk");
	if(p)//if p isnt null then
		printf("base: %c\n",*p);
//	printf("%p\n",*p);

}

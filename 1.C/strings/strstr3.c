//searching for a string in a given string

#include<stdio.h>

char *func(char *str,char *sub){
	
	int sz = strlen(sub);
	while(*str && strncmp(str,sub,sz)){
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

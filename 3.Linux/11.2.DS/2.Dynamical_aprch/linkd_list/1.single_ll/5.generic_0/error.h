#include<string.h>
#include<stdio.h>

int errno;

enum err{

	EEND = -6,
	EFOUND=-5,
	EMALL=-4,
	EEPTY=-3,
	EFULL,
	FAILURE,
	SUCCESS,

};

void errmsg(char *str){

	switch(errno){
			
			case EEND:
					printf("%s: Reached end of list\n",str);
					break;
			case EFOUND:
					printf("%s: Element not found\n",str);
					break;
			case EEPTY:
					printf("%s: Q is empty\n",str);
					break;
			case EFULL:
					printf("%s: Q is full\n",str);
					break;
			case EMALL:
					printf("%s: Failed in alloc mem\n",str);
					break;
			case FAILURE:
					printf("%s: Failed\n",str);
					break;
			case SUCCESS:
					printf("%s: Success\n",str);
					break;
			default   :
					printf("No errno is set\n",str);
					break;
	}

}

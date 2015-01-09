#include<stdio.h>

#ifndef _ERR

#define _ERR

int errno;

enum err{

	EEPTY=-4,
	EMALL,
	EFOUND,
	FAILURE,
	SUCCESS
	};

void errmsg(char *str){

	switch(errno){

                        case EFOUND:
                                        printf("%s: Element not found\n",str);
                                        break;
                        case EEPTY:
                                        printf("%s: Q is empty\n",str);
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
#endif

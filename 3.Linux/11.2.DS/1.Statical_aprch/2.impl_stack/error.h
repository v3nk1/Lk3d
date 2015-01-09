#include<string.h>

int errno;

/*#define SUCCESS 0
#define FAILURE -1
#define EFULL -2
#define EEPTY -3
*/
/*#define EFULL -4
#define EFULL -5
#define EFULL -6
#define EFULL -7
#define EFULL -8
#define EFULL -9
#define EFULL -10
#define EFULL -11
*/

//OR u can use enum

enum err{
	
	EEPTY=-3,EFULL,FAILURE,SUCCESS

	};

void errmsg(char *str){

	switch(errno){

		case SUCCESS:	
				printf("%s: Success\n",str);
				break;
		case FAILURE:	
				printf("%s: Failed\n",str);
				break;
		case EFULL:	
				printf("%s: Stack is full\n",str);
				break;
		case EEPTY:	
				printf("%s: Stack is empty\n",str);
				break;

		default	  : 	
				printf("Errno is not loaded\n");
				break;
	}

}

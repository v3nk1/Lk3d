#include<stdio.h>
extern void menu(void);
extern void menuHandler(char);

main(){


while(1) {
	
	menu();
	char cho;
	printf("enter your choice: ");
	scanf(" %c",&cho);
	if(cho=='E'||cho=='e'){
		printf("Are you sure [y/n]: ");
		char _exit;
		scanf(" %c",&_exit);
		if(_exit=='y'||_exit=='Y') break;
		else continue;
		}
	menuHandler(cho);
	}

}

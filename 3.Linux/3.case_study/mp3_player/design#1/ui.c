#include<stdio.h>
extern void menu(void);
extern void menuHandler(char);
main(){
while(1) {
	menu();
	char cho,reg;
	printf("enter your choice: ");
	scanf(" %c",&cho);
	if(cho=='E'||cho=='e'){
			 printf("are you sure [y/n]: ");
			 scanf(" %c",&reg);
			 if(reg=='y'|| reg=='Y') break;
			 else  continue;
			}
	menuHandler(cho);
	}
}

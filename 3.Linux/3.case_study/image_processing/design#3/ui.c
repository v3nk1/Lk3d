#include<stdio.h>
#include"headers.c"
#include<dlfcn.h>
extern void *lib;

extern void vloadHandlers(void);

void disp_menu(void){
int cho;
while(1){
	
	printf("1.show image\n");
	printf("2.conv image\n");
	printf("3.exit\n");
	printf("enter ur choice:");
	scanf(" %d",&cho);
if(cho==3) {//dlclose(lib); //after completion of prog ie., end curly brace of main() automatically _fini excutes , ie., here unregistering 3 handlers takes place.  
		break;
		}
if(cho==1||cho==2){
	handleMenuEvent(cho);
	}	
else printf("******************** INVALID CHOICE **********************\n"),printf("TRY AGAIN\n");
}}

void handleMenuEvent(int cho){
char name[25];
printf("enter name of file:");
scanf("%s",name);
	switch(cho){
		case 1://printf("success\n");
			vdisplayImage(name);
			break;
		case 2:
	//	printf("success\n");
			vsaveImage(name);		
			break;
			
		default:
			printf("invalid choice\n");

		}				

}

main(){
	vloadHandlers();
	disp_menu();
		

}

#include<stdio.h>
#include"headers.c"
int disp_menu(void){
	int cho;
	printf("1.show image\n");
	printf("2.conv image\n");
	printf("3.exit\n");
	printf("enter ur choice:");
	scanf(" %d",&cho);
if(cho==1||cho==2||cho==3) return cho;	
else {printf("******************** INVALID CHOICE **********************\n");printf("TRY AGAIN\n");return -1;}
}

void handleMenuEvent(int cho){
char name[25];int ret;
printf("enter name of file:");
scanf("%s",name);
	switch(cho){
		case 1:
			vdisplayImage(name);
			break;
		case 2:
			vsaveImage(name);		
			break;
			
		default:
			printf("invalid choice\n");

		}				

}
main(){
char name[23];
int cho;
while(1){	
	cho=disp_menu();
	if(cho==3) break;
	if(cho!=-1)handleMenuEvent(cho);
	}	
}

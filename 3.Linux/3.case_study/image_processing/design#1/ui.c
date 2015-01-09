#include<stdio.h>
#include<stdlib.h>

extern void showImage(void);
extern void convImage(void);
void menu(void){
	printf("1.show image\n");
	printf("2.conv image\n");
	printf("3.exit \n");
		
	
}

main(){
int cho;
while(1){
	menu();
	cho=0;
	printf("enter choice:");
	scanf(" %d",&cho);
	switch(cho){
		case 1:
			showImage();
			break;

		case 2:
			convImage();
			return;
		case 3: 
			return;
			//exit(1);

		default:
			printf("TRY AGAIN\n");
			
	}
}
}

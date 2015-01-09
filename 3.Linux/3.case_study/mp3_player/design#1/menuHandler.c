#include<stdio.h>

extern void loadMedia(void);
extern void playMedia(void);
extern void stopMedia(void);
extern void pauseMedia(void);

void menuHandler(char cho){
	
	switch(cho){
		case 'o': loadMedia();
			   	break; 
		case 'p': playMedia();
			   	break; 
		case 's': stopMedia();
			  	break; 
		case 'r': pauseMedia();
			   	 break; 
		default:
			printf("INVALID INPUT\n");
		}



}

#include<stdio.h>

extern void vloadMedia(void);
extern void vplayMedia(void);
extern void vstopMedia(void);
extern void vpauseMedia(void);
extern void vconvert(void);

void menuHandler(char cho){
	
	switch(cho){
		case 'l': vloadMedia();
			   	break; 
		case 'p': vplayMedia();
			   	break; 
		case 's': vstopMedia();
			  	break; 
		case 'r': vpauseMedia();
			   	 break;
		case 'c': vconvert();
				break; 
		default:
			printf("INVALID INPUT\n");
		}



}

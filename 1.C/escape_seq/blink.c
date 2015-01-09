//Here in this prog, we are not using '\r', so here the diff is we are having loading constantly on the screen and dots only blinking..
	//in the next program we are printing "Loading" msg also repeatedly for every iteration of while loop..

#include<stdio.h>

void blink_dot(void){

	int i=0,j=0;

	while(j++ <= 2){

	for(i=0;i<3;i++){

	fflush(stdout);//must and shud see the man page of it.. its used bcoz of immediate invoking of printf(prints user buffer data),Otherwise printf prints data after full of block driver size reached..
	usleep(500000);
	printf(".");

	}

	if(i==3)  i=0;

	fflush(stdout);
	usleep(500000);
	printf("\b\b\b");// '\b' doesnt erase just goes to 3 position back
	printf("   ");//to erase 3 dots(actually we are replaces those dots with spaces)
	printf("\b\b\b");//again control goes 3 pos back

	}

	printf("\n\n");

}

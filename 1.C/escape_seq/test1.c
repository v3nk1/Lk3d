//In second while iteration the control comes to "L"

#include<stdio.h>

main(){

	int i=0;

	while(1){

		printf("Loading ");

		for(i=0;i<3;i++){

			fflush(stdout);
			usleep(500000);
			printf(".");

			}

	if(i==3)  i=0;

	fflush(stdout);
	usleep(500000);

	printf("\b\b\b");// '\b' doesnt erase just goes to 3 position back
	printf("   ");//to erase 3 dots(actually we are replaces with spaces)
	printf("\r");//go to start position means "L" position in loading

	}

}

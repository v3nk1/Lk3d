#include<unistd.h>
#include<stdlib.h>

main(){

	int p=access("../char.c",X_OK);
	if(p==-1) 
		perror("access"),exit(45645);
	printf("%d\n",p);

}

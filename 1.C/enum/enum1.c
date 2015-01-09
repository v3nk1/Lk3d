#include<stdio.h>

main(){

	enum /*errno*/{ //no need of tag
		jan=-10,feb,mar,apr
		};

	printf("jan= %d,%d,%d,%d\n",jan,feb,mar,apr);

}

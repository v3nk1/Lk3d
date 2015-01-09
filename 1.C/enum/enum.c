#include<stdio.h>
#include<stdlib.h>

main(){

	enum tag{
		jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
		};

	enum tag m=dec;

	printf("%d\n",m);

}

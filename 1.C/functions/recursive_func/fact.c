#include<stdio.h>

int fact(int no){

	if(no<0) return -1;
	int res=1;
	if(no){
		res=no;
		res*=fact(--no);
	}
	return res;
}

main(){

	printf("fact: %d\n",fact(5));

}

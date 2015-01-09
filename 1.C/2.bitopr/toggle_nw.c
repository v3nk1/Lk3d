#include<stdio.h>

//to toggle the given input as spcefied no., of bits..

void pb(unsigned int,int);

unsigned int toggle(unsigned int i,int pos,int no_bits){

	unsigned int ret;
	ret = 0xffffffff;
	ret=ret>>pos;
	ret = ret<<(32-no_bits);
	ret= (ret>>(32-no_bits-pos))^i;

return ret;

}

void pb(unsigned int res,int size){

	int i;

	for(i=size*8-1;i>=0;i--){
	//printf("%d  ",i);
	printf("%d ",1 & (res>>i));

	if(i%8==0) printf("   ");
	}

printf("\n");

}

main(){

	unsigned int a,pos,no_bits;
	loop:
	printf("enter a(hex),pos,no_bits:");
	scanf("%x%d%d",&a,&pos,&no_bits);
	
	if(pos>=0 && pos<=31){
	unsigned int res = toggle(a,pos,no_bits);
	
	pb(res,sizeof(int));

	}
	else
		goto loop;
}

/*
 * Write a program to reverse bits starts from given position(travrs) to given no.. of count (upto);
 */

#include <stdio.h>

void pb(unsigned long val,int sz){

	int i;
	for(i=(sz*8)-1;i>=0;i--){
		if(i!=(sz*8)-1 && (i+1)%8==0)
			printf(" ");
		printf("%d",val & 1<<i ? 1 : 0);
		}
	printf("\n");

}


unsigned long generate_bits(int sz,int pos){
						//pos is holding pos'th bit shud be zero,rest of all bits as 1.
	unsigned long gen0;
	int i;
	gen0=0;
	for(i=sz*8-1;i>=0;i--){
		if(i!=pos)
			gen0|=1<<i;
		}
//	gen0=~gen0;
//printf("Generated:\n");
//pb(gen0,sizeof(int));
	return gen0;
}

void rev_bits(unsigned val,int trav,int upto){

	unsigned long gen;
	unsigned bkp;
	int i;

	for(i=0;i<upto/2;i++){
		bkp= 1<<trav-i+1-upto & val ? 1:0;
		gen=generate_bits(sizeof(val),trav-i+1-upto);
		val= 1<<trav-i & val ? val|~gen : val&gen ;
		gen=generate_bits(sizeof(val),trav-i);
		val= bkp ? val|~gen : val&gen;
//		printf("$%d\n",trav-i);
//		printf("$%d\n",trav-i+1-upto);
//		printf("#%d ",bkp);
//		bkp1= 1<<trav-i+1-upto & val ? 1:0;
//		val= val | (bkp << trav-i+1-upto);
//		val= val | (bkp1 << trav);
	}
	pb(val,sizeof(val));
}

main(){

	unsigned val=0x1234;
	int travrs;
	int upto;

	printf("Enter travers: ");
	scanf("%d",&travrs);
	printf("Enter upto: ");
	scanf("%d",&upto);
	if(upto>travrs){
		printf("Input error\n");
		return;
		}
	pb(val,sizeof(val));
	rev_bits(val,travrs,upto);
}

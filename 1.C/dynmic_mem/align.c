#include<stdio.h>
#include<stdio.h>

main(){

	void *p1,*p2,*p3,*p4;
	p1=malloc(100);
			/* Aligns memory by:
			   	16bytes on 64 bit
			   	8bytes on 32bit   gcc -m32 align.c
			 */

	p2=memalign(512/*1024*/,100);//it gives aligned memory as requested
	posix_memalign(&p3,512/*1024*/,100);// it gives alignement as multiples of 1024

	printf("p1:%d\n",((long long int)p1) % /*8*/16);
	printf("p2:%d\n",((long long int)p2) % 512);
	printf("p3:%d\n",((long long int)p3) % 1024);

}

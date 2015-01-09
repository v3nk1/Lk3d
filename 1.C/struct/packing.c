/*
 * Packing is to tell the compiler that do strict alignment instead of zero padding.
 * 1. Inline assembly is one approach.
 * 2. compile with "-fpack-struct" flag, to enable the packing.
	Ex: cc -fpack-struct filename.c
 * 3. Use 
	#pragma pack(n)
		n: the alignment u wanted to be, but must be powers of 2; 2^0, 2^1, 2^2 ...
		To get strictly packed use '1'
 	Ex: #pragma pack(1)
	
 */


#include<stdio.h>
//#pragma pack(1)

//struct __attribute__((__packed__)) abc{
struct abc{

	int a;
	char ch;

	};
struct  ABC{
//struct __attribute__((__packed__)) ABC{

	short a;
	char ch;

	};

main(){

	struct abc x;
	int k;
	struct ABC y;
	
	printf("Size(x): %lu, Size(y): %lu\n",sizeof(x),sizeof(y));

	printf("&x\t: %llu\n&(x.a)\t: %llu\n&(x.ch)\t: %llu\n&y\t: %llu\n&k\t: %llu\n",&x,&(x.a),&(x.ch),&y,&k);

}	

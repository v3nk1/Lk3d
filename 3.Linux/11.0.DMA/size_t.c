//cc size_t.c and ./a.out		o/p: 8
//cc -m32 size_t.c and ./a.out 		o/p: 4

#include<stdio.h>

main(){

	printf("%lu\n",sizeof(size_t));   //size_t = unsigned long int.
						//sizeof(unsigned long int) = 8(in 64bit), 4(in 32bit)

}

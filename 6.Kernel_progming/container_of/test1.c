#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr)-(char *)(&((type *)0)->member)))
		//Always gives the base address of the structure
	
struct alphbt {
	
		int a;
		int b;
		int c;
		short d;
		long e;
		char f;
		long long g;
		int h;
		int i;
		int j;
		int k;
		int l;
		int m;
		int n;
		int o;
		int p;
		int q;
		int r;
		int s;
		int t;
		int u;
		int v;
		int w;
		int x;
		int y;
		int z;

	};

main(){

	struct alphbt *ptr=malloc(sizeof(struct alphbt));

	printf("Original: %p\n",ptr);

	printf("Obtained: %p\n",container_of(&ptr->e,struct alphbt,e));

}	

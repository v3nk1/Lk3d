#include"./headers/dcll_gen.h"
#include"./headers/errmsg.h"
#include<stdio.h>

struct asdf{
	int a;
	int b;
	}v,k;

main(){

	dcll_t l1;
	dcll_init(&l1);

	v.a = 10;
	v.b = 20;
	k.a=100;
	k.b=200;

	printf("%p\n",&v);
	retrive(l1,10);
	errmsg("retrive");
	insert_first(&l1,&v,"struct asdf");
	insert_first(&l1,&v,"struct bsdf");
	print_id(l1);
	printf("%p\n",retrive(l1,1));

}

#include<stdio.h>

struct A{
	int a;
	}o;

int update(struct A o,int load){
	o.a=load;
	return o.a;
}

main(){

	o.a=2;
	o.a=update(o,6);
	printf("%d\n",o.a);

}

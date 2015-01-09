#include<stdio.h>
#include<stdlib.h>


main(){

	int size_ma,size_re,i;
	printf("enter size of dyn_memory u wnt to create in bytes: ");
	
	scanf("%d",&size_ma);
	int *p=malloc(size_ma);
	if(p==NULL) printf("NO MEMORY AVAILABLE IN HEAP\n");

	printf("enter d ele: ");
	for(i=0;i<size_ma/sizeof(*p);i++) scanf(" %d",p+i); // here sizeof(*p) used becoz to make it geniric, if u give 20 bytes and p is declared as pointer to interger then sizeof(p) or any pointer is 8b(in 64bit) & 4b(in 32bit). so derefering *p returns integer in above case so sizeof it is 4b. so we are able to run for loop for 5 times.(so that 5 integer values can be stored).
	
	for(i=0;i<size_ma/sizeof(*p);i++) printf("%d ",*(p+i));
	printf("\n");
	//for(i=0;i<5;i++) printf("%lu ",(p+i));printf("\n");

	//free(p);  if u free above data will be lost..
	
	printf("how much memory u want to increase(realloc):");
	scanf("%d",&size_re);
	p=realloc(p,size_re);
	
	printf("enter the elememts to be append: ");
	for(i=size_ma/sizeof(*p); i< (size_re+size_ma)/sizeof(*p) ;i++) scanf(" %d",p+i);
	
	for(i=0; i< (size_re+size_ma)/sizeof(*p) ;i++) printf("%d ",*(p+i));
	printf("\n");
	//for(i=0;i<9;i++) printf("%lu ",(p+i));printf("\n");

}

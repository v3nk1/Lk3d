#include<stdio.h>

typedef struct node{

                void *data;
                struct node *next;
        }*list_t;


main(){

	list_t l1=NULL;
	printf("l1 = %lu\n*l1=%lu\n &l1=%lu\n",sizeof(l1),sizeof(*l1), sizeof(&l1)); //the middle one *l1 doesnt cause segmentation fault.
//	printf("l1 = %lu\n*l1=%lu\n &l1=%lu\n",sizeof(l1),sizeof(*NULL), sizeof(&l1));

}

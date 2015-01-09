#include<stdio.h>
#include"stack.h"

main(){

	stack_t s1,s2;

	stack_init(&s1);
	stack_init(&s2);

	push(&s1,10);
	push(&s1,20);
	push(&s1,30);
	push(&s1,40);
	push(&s1,50);
	
        push(&s2,100);
        push(&s2,200);
        push(&s2,300);
        push(&s2,400);
        push(&s2,500);

	printf("\nAfter push:\n");
	disp_stack(s1);
	disp_stack(s2);

	printf("\ns1 top: %d\n",peek(s1));
	printf("s2 top: %d\n",peek(s2));

	pop(&s1);
	pop(&s2);

	printf("\nAfter pop:\n");
	disp_stack(s1);
	disp_stack(s2);

	stack_init(&s1);
	printf("\nAfter flush:\n");
	if(pop(&s1) == -1) errmsg("pop");
	if(disp_stack(s1)==-1) errmsg("disp_stack");


}

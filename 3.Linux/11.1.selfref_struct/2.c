//write a self referential structure, that will capable of holding next address 

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct memory{
	
	int data;
	struct memory *next;

};

void print(struct memory *start){

	struct memory *tmp = start;

	while(tmp){
		printf("%d\n",tmp->data);
		tmp = tmp->next;
		}

}

main(){

	struct memory *start,*tmp;

	start= malloc(sizeof(*start));

	start->data = 10;
	start->next = NULL;

	start->next = tmp = malloc(sizeof(*start));
	
	tmp->data = 20;
	tmp->next = NULL;

	print(start);

}

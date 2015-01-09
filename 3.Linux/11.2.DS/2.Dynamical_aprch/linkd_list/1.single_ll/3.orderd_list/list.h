#include<stdio.h>
#include<malloc.h>
#include"error.h"

typedef struct node{
	int data;
	struct node* next;
	}list_t;

//list_t *start; now i'm giving it to user

void list_init(list_t **start){

	bzero(start,sizeof(list_t));

	}

int insert(list_t **_start,int val){//always inserts an ele in ascending order

	list_t *start = *_start;
	list_t *_new;

	_new = malloc(sizeof(list_t));
		if(!_new){
			errno = EMALL;
			return FAILURE;
			}	

	if(!start){
		start = _new;
		_new -> data = val;
		_new -> next = NULL;	

		*_start = start;//updating in users list ptr
		return (errno = SUCCESS);

		}

	if(!start->next){
		if(val < start->data){
                        _new->next = start;
                        start = _new;
                        _new->data = val;

			*_start = start;
                        return (errno = SUCCESS);
                        }
		else{
			 start->next = _new;
                        _new->data = val;
                        _new->next = NULL;
                        return (errno = SUCCESS);

			}

		}


	list_t *tmp = start,*prev=NULL;
	while(tmp){ //for val < ele already present
		
		if(val < tmp->data ){
			if(prev){
				_new->next = tmp;
				_new->data = val;
				prev->next = _new;
				return (errno = SUCCESS);
				}
			else{
				_new->next = tmp;
                                _new->data = val;
				*_start = _new;
				return (errno = SUCCESS);
				}
			}
		prev = tmp;
		tmp = tmp->next;
		}
		
		prev->next = _new;
		_new->next = NULL;
		_new->data = val;
		
		*_start = start;
	
	return SUCCESS;
	
}

int print(list_t *start){

	if(!start){
		errno = EEPTY;
		return FAILURE;
		}
	
	list_t *tmp = start;
	while(tmp){
		printf("%d ",tmp->data);
		tmp = tmp->next;
		}

	printf("\n");

	return (errno = SUCCESS);
}

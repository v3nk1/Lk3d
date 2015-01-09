#include<stdio.h>
#include<malloc.h>
#include"error.h"

typedef struct node{

	int data;
	struct node *next;
	struct node *prev;

	}node_t;

node_t *start;  //Only one list maintained

int insert_first(int val){

	node_t *_new;
	_new = malloc(sizeof(node_t));
		if(!_new){
			errno = EMALL;
			return FAILURE;
			}

	if(!start){ //empty list
		_new -> data = val;
		_new -> next = NULL;
		_new -> prev = NULL;
		start = _new;
		return (errno = SUCCESS);
		}
		
	if(start){//if some elements are there
		//node_t *tmp = start;
		start->prev = _new;
		_new->data = val;
		_new->next = start;
		_new->prev = NULL;
		start = _new;

	return SUCCESS;
	}

}

int del_last(void){

	
	if(!start){
		errno = EEPTY;
		return FAILURE;
		}

	if(!start->next){ //single element case if u use below one for this case it causes segmentation fault..
		node_t *tmp=start;
		start = NULL;
		free(tmp);
		return (errno = SUCCESS);
		}

	node_t *tmp = start;
	while(tmp->next){//dnt use tmp if u use tmp only then u hav to backup the tmp in _prev; as bellow
		//node_t *_prev=start;
		tmp = tmp ->next;
		}
		tmp->prev->next = NULL/*NULL*/;

	free(tmp);
	return (errno = SUCCESS);

}

int sort_list(void){//ascending order

	if(!start){//if list is empty
		errno = EEPTY;
		return FAILURE;
		}

	node_t *tmp = start;
	while(tmp->next){//if list has >1 elements  (it fails if list has only one element since "tmp->next = NULL")

		node_t *_tmp = start;

		while(_tmp->next){
			if(_tmp->data > _tmp->next->data){
					int swap = _tmp -> data;
					_tmp -> data = _tmp->next->data;
					_tmp->next->data = swap;
				}
			_tmp = _tmp -> next;
			}
		tmp = tmp -> next;
	}
	
	/*if list has only one element no need to sort*/
	return (errno = SUCCESS);

}

int disp_list(void){

	node_t *tmp=start;
	if(!tmp){

		errno = EEPTY;
		return FAILURE;

		}

	while(tmp){
		
		printf("%d ",tmp->data);
		tmp = tmp->next;

		}
	printf("\n");

	return (errno = SUCCESS);	
}

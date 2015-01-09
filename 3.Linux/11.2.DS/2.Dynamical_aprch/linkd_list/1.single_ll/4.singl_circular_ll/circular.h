#include"error.h"
#include<malloc.h>
#include<string.h>

typedef struct circular{
	int data;
	struct circular *next;
	}*circ_t;

void circ_init(circ_t *circ){

	bzero(circ,sizeof(*circ));

}

int insert_first(circ_t *circ,int val){

	circ_t _new;
	
	_new = malloc(sizeof(*circ));
	if(!_new){
		errno = EMALL;
		return FAILURE;
		}

	_new ->data = val;

//	printf("circ = %p\n",*circ);

	if(!(*circ)){
		
		*circ = _new;
		_new -> next = *circ;
		return (errno = SUCCESS);

		}

	circ_t prev=*circ,tmp = (*circ)->next;//tmp will be distroyed when the function returns to calling fuction since tmp is local to this block only.. intialize tmp with *circ; initialize with (*circ)->next.
		//initialise prev = *circ, if assign NULL or leave it alone(garbage) causes segmentation fault.. bcoz if u want to know the concept give NULL and anlize for 2nd element case..
	while(tmp != *circ){
		prev = tmp;
		tmp = tmp->next;
		}
	prev -> next = _new;
	_new -> next = *circ;
	*circ = _new;
		
	return (errno = SUCCESS);

}

int insert_last(circ_t *circ,int val){

	circ_t _new;
	_new = malloc(sizeof(*circ));
	if(!_new){
		errno = EMALL;
		return FAILURE;
		}
	
	_new->data = val;
	if(!(*circ)){
		*circ = _new;
		_new->next = _new;
		return (errno = SUCCESS);
		}

	circ_t tmp = *circ;//,prev=*circ;
	while(tmp->next != *circ){
		
		//prev = tmp;
		tmp = tmp->next;
		
		}
		tmp->next = _new;
		_new->next = *circ;
	
	return (errno = SUCCESS);

}

int print_circ(circ_t circ){

	if(!circ){
		errno = EEPTY;
		return FAILURE;
		}

	if(circ->next == circ){
		
		printf("%d\n",circ->data);
		return (errno = SUCCESS);
		
		}
		

	circ_t tmp = circ->next;
	printf("%d ",circ->data);
	while(tmp != circ){

		printf("%d ",tmp->data);
		tmp = tmp->next;
		
	}
	printf("\n");
	return (errno = SUCCESS);

}

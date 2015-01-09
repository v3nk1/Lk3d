#include<stdio.h>
#include<malloc.h>
#include"error.h"

typedef struct node{
		
		void *data;
		struct node *next;
	}*list_t;

/*
struct dtypes{

	void (*intgr)(list_t,int *);
	void (*ch)(list_t,char *);
	void (*struct_func)(struct *) 

	}
*/

int list_init(list_t *list){

	bzero(list,sizeof(*list));

	return (errno = SUCCESS);
	}

int insert_first(list_t *list,void *dptr){
	
	list_t _new;

	_new = malloc(sizeof(**list));
		if(!_new){
			errno = EMALL;
			return FAILURE;
			}

	_new->data = dptr;

	if(!(*list)){
			_new->next = NULL;
			(*list) = _new;
			return (errno = SUCCESS);
		}
		
	
	_new->next = *list;
	*list = _new;
	return (errno = SUCCESS);
	
}

int read_list(list_t list,list_t *list_cur_pos){// it return tmp address on success(since to navagate for 2nd node for 2nd time of this function has invoked)

	static cnt;

	if(!list){
		errno = EEPTY;
		return FAILURE;
		}
	if(!(*list_cur_pos)){
		errno = EEND;
		return FAILURE;
		}

	if(cnt<1){
		cnt++;
		return (errno = SUCCESS);
		}	
	
	(*list_cur_pos) = (*list_cur_pos)->next;
	cnt++;

	return (errno = SUCCESS);

}

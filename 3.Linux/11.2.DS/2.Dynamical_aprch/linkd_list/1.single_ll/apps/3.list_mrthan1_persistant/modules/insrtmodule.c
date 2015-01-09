#include<stdio.h>
#include"../headers/nheaders.h"
#include"../headers/errno.h"
#include"../headers/lheaders.h"


/*********************************************** INSERTION FUNCTIONS ***********************************************************/


#define start (*_list)->lstart             //start has declared in headers.h


int insert_last(list_t **_list){ 


	int val;
	printf("enter the element u want to enque:");
	scanf(" %d",&val);

	que_t *_new;

	_new = malloc(sizeof(que_t));
			if(!_new){
				errno = EMALL; 
				return FAILURE;
			  }

	(*_list)->cnt++;  //increments the no of nodes in a particular list..
/*case1: if the given ele is first ele of stack*/
				
	if(!start){
			
		start = _new; 	//to dont loose the reference of starting node..

		_new -> data = val;
		_new -> next = NULL; //to identify end of que..
		
		return (errno = SUCCESS);

        	}
	

/*case2: if there is some elements already exists */

	if(start){
	
		que_t *prev = start;

		while(prev->next)    //very very importent..
			prev = prev->next;

		prev->next = _new;

		_new -> data = val;
		_new -> next = NULL;
		
		return (errno = SUCCESS);

	}
		
}

int insert_first(list_t **_list){
	
	int val;
	printf("enter the element u want to enque: ");
	scanf(" %d",&val);
	
	que_t *_new;
	
	_new = malloc(sizeof(que_t));
	if(!_new){
		errno = EMALL;
		return FAILURE;
		}
	
	(*_list)->cnt++;
	/*for empty que*/
	if(!start){
		_new->data = val;	//u indirectly updating start pointed data only
		_new->next = start/* NULL*/;
		start = _new;
		return (errno = SUCCESS); //if no return statement bellow statements will also going to execute..
		}		

	/*if Q has 1/some elements*/  //this is suffiecient for above empty case also..
	_new->data = val;
	_new->next = start;
	start = _new;
	
	return (errno = SUCCESS);

}

int insert_bulk(list_t **_list){

loop:
/*==>*/	{
	int blk;
	insert_bulk_menu();
	printf("enter choice: ");
	scanf(" %d",&blk);
	
	if(blk == 1){
		int cnt=0,iter;//iterations
		printf("how many entities: ");
		scanf(" %d",&iter);

		while(1){
			if(insert_first(_list)==-1){
				errmsg("insert_first");
				break;
				}
			
			cnt++;
			if(cnt==iter) break;
			
		}
	   goto loop;
	}
	if(blk == 2){
		int cnt=0,iter;//iterations
                printf("how many entities: ");
                scanf(" %d",&iter);

                while(1){
                        if(insert_last(_list)==-1){
                                errmsg("insert_last");
                                break;
                                }

                        cnt++;
                        if(cnt==iter) break;

                }
	goto loop;
        }

	if(blk == 0)
		return;
	
	else{

		printf("No such choice\n");
		goto loop;	
			
		}
/*==>*/	}
}



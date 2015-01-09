#include<stdio.h>
#include"../headers/nheaders.h"
#include"../headers/errno.h"
#include"../headers/lheaders.h"

/******************************************************  DISPLAY FUNCTIONS *****************************************************/

#define start _list->lstart

/*displays list as is */
int disp_que(list_t *_list){  //when printing think that we are inserting ele from right to left direction,

	que_t *tmp = start;
/*que is empty*/
	if(!tmp){
		errno = EEPTY;
		return FAILURE;
		}

/*que has some ele's*/
	while(tmp){

		printf("%d ",tmp->data);
		tmp = tmp->next;
	}
	
	printf("\n");
	
	return (errno = SUCCESS);
}

/*displays list ascending order(but doesnt effect the list., means no element in the list doesnt effect they will like as the order u stored)*/
void find_max_min(list_t *_list,int *max,int *min);
int disp_list_asc(list_t *_list){

	que_t *tmp = start;
	if(!tmp){//for empty list..
		errno = EEPTY;
		return FAILURE;
		}
	
	if(!tmp->next){//for one element list..
		printf("%d ",tmp->data);
		return (errno = SUCCESS);
		}

	int prev_swap=INT_MIN;// for this include<limits.h>
	int min,max;
	find_max_min(_list,&min,&max);

	while(tmp){
		int swap = max;
		que_t *_tmp = start;
		while(_tmp){//dnt give _tmp->next it will fail for last ele
			
			if((_tmp->data > prev_swap) && (_tmp->data < swap)){
				swap = _tmp->data;
				}
			_tmp = _tmp->next;
			}
		
			printf("%d ",swap);
		prev_swap = swap;
		tmp = tmp->next;
		}
	printf("\n");
	return (errno = SUCCESS);
}

void find_max_min(list_t *_list,int *min,int *max){

	que_t *tmp = _list->lstart;
	
	if(!tmp){//if no element in the list there is no use of this function..
		//no need to set errno, since end user cannt invoke it..
		return;
		}

	if(!tmp->next){ //if only one ele no use of this function
			return;
		}
		
	*min = start -> data;
	*max = start -> data;
	while(tmp){
		
		if(tmp->data < *min){
				*min = tmp->data;
				}
		if(tmp->data > *max){
				*max = tmp->data;
				}	
		tmp = tmp->next;

		}

}	

/*displays list descending order(but doesnt effect the list., means no element in the list doesnt effect they will like as the order u stored)*/

int disp_list_dsc(list_t *_list){

	que_t *tmp = start;	
	
	if(!tmp){//for empty list
		errno = EEPTY;
		return FAILURE;
		}

	if(!tmp->next){//for 1 ele list

		printf("%d\n",tmp->data);
		return (errno = SUCCESS);

		}
	
	int min,max;
	find_max_min(_list,&min,&max);//if u invoke it at the start of the function then causes segmentation fault
	
	int prev_val=INT_MAX;

	while(tmp){
		int val = min;
		que_t *_tmp = start;
		while(_tmp){

			if(_tmp->data < prev_val && _tmp->data > val){
												
						val = _tmp->data;	
											
					}
			_tmp= _tmp->next;
			}
		prev_val = val;
		printf("%d ",val);
		tmp = tmp->next;
	}

	printf("\n");

return (errno = SUCCESS);

}

void revorder(que_t *tmp){

	if(!tmp->next){
		printf("%d ",tmp->data);
		}
	else{
		revorder(tmp->next);
		printf("%d ",tmp->data);
	}

}

int disp_list_rev(list_t *_list){
	
	if(!start){
		errno = EEPTY;
		return FAILURE;
		}
	if(!start->next){
		printf("%d\n",start->data);
		return SUCCESS;
		}

	que_t *tmp = start;
	revorder(tmp);
	printf("\n");
	return (errno = SUCCESS);
	}

#include<stdio.h>
#include"../headers/errno.h"
#include"../headers/nheaders.h"
#include"../headers/lheaders.h"

#define start (*_list)->lstart

/**************************************************** DELETION FUNCTIONS ********************************************************/

/*Always deletes the first element in the que */
int del_first(list_t **_list){


	que_t *tmp = start;
	
/*Q has no ele*/
	if(!tmp){
		errno = EEPTY;
		return FAILURE;
		}

/*it has some elements >0*/	
	start = tmp->next;

	tmp->next = NULL;
	(*_list)->cnt--;//used to display how many nodes in a list..
	free(tmp);
	
return (errno = SUCCESS);	
	
}	

/*always delete last ele in the Q*/
int del_last(list_t **_list){

	que_t *tmp = start;
	
	if(!tmp){//already que empty 
		errno = EEPTY;
		return FAILURE;
		}

	/*only one ele in que*/
	if(!tmp->next){
		start = NULL;
		(*_list)->cnt--;
		free(tmp);
		return (errno = SUCCESS);
		}
	

	que_t *prev;
	while(tmp->next){
		prev = tmp; //to make "prev_node->next" of deleting node to NULL we take its back up into prev. Since rear end of the que must be end with NULL..
		tmp = tmp->next;
		}

	prev -> next = NULL;
	(*_list)->cnt--;
	free(tmp);
	return (errno = SUCCESS);

}

int del_ele(list_t **_list){

	int val;
	printf("enter the ele: ");
	scanf(" %d",&val);

	que_t *tmp = start;

	if(!tmp){
		errno = EEPTY;
		return FAILURE;
		}
	/*if delting ele is 1st ele in que*/
	if(tmp -> data == val){
			start = tmp -> next;
			(*_list)->cnt--;
			free(tmp);
			return SUCCESS;
			}
			
	/*if some ele are there in que >1; u r deleting middle(not first/last) ele */
	que_t *prev;
	while(tmp->data != val){
				prev = tmp;
				if(!tmp->next){//ele is not found
						errno = EFOUND;
						return FAILURE;
					}
						
				tmp = tmp->next;
				}
			
			prev -> next = tmp->next;
			(*_list)->cnt--;
			free(tmp);
	
	/*del ele is last ele*/	
		//even for last element case above function will work

	return (errno = SUCCESS);
	
}

int flush(list_t **_list){//delete entire list

	while(start){
		que_t *next = start ->next;
		free(start);
		start = next;
		}
	(*_list)->cnt = 0;
//	start = NULL; no need bcoz by the time start comes out of loop(fails bcoz of NULL) its value = NULL only na..
	
	return (errno = SUCCESS);

}

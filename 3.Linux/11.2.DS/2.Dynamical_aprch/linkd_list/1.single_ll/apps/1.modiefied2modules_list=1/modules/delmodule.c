#include<stdio.h>
#include"../errno.h"
#include"../headers.h"



/**************************************************** DELETION FUNCTIONS ********************************************************/

/*Always deletes the first element in the que */
int del_first(void){

	que_t *tmp = start;
	
/*Q has no ele*/
	if(!tmp){
		errno = EEPTY;
		return FAILURE;
		}

/*it has some elements >0*/	
	start = tmp->next;

	tmp->next = NULL;

	free(tmp);
	
return (errno = SUCCESS);	
	
}	

/*always delete last ele in the Q*/
int del_last(void){

	que_t *tmp = start;
	
	if(!tmp){//already que empty 
		errno = EEPTY;
		return FAILURE;
		}

	/*only one ele in que*/
	if(!tmp->next){
		start = NULL;
		free(tmp);
		return (errno = SUCCESS);
		}
	

	que_t *prev;
	while(tmp->next){
		prev = tmp; //to make "prev_node->next" of deleting node to NULL we take its back up into prev. Since rear end of the que must be end with NULL..
		tmp = tmp->next;
		}

	prev -> next = NULL;
	
	free(tmp);
	return (errno = SUCCESS);

}

int del_ele(void){

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
			
			free(tmp);
	
	/*del ele is last ele*/	
		//even for last element case above function will work

	return SUCCESS;
	
}

int flush(void){//delete entire list

	while(start){
		que_t *next = start ->next;
		free(start);
		start = next;
		}
//	start = NULL; no need bcoz by the time start comes out of loop(fails bcoz of NULL) its value = NULL only na..
	
	return (errno = SUCCESS);

}

int del_all_dups(void){//considered the 1st founded ele is the original and rest of all dups, so it will deletes rest all except what it holds for checking..

	if(!start){

		errno = EEPTY;
		return FAILURE;
		}
	
	que_t *tmp = start;

	if(!tmp->next){
			errno = ENODUP;
			return FAILURE;
		}
	
	que_t *_tmp = start;

while(_tmp){
	int search=_tmp->data;
	
	tmp = _tmp -> next;
	que_t /**noneed=NULL,*/*prev=start;
loop:	while(tmp && (tmp->data != search) ){
		
			prev = tmp;
			tmp = tmp -> next;
			
			}
	
	if(tmp){//the above condition fails if search ele equals or if tmp reached end of list.. so that why i'm checking tmp is NULL or not
		prev->next = tmp->next;
		free(tmp);
		tmp = prev->next;
		goto loop;
		}
	_tmp=_tmp->next;
}

return (errno = SUCCESS);

}

int del_ele_dups(void){//it will search for given ele dups and deletes if found any..
			//it will consider first occurence of the given element as original after if any considered as dups

	int val,cnt=0;
	
	if(!start){

		errno = EEPTY;
		return FAILURE;
		}
	if(!start->next){

		errno = ENODUP;
		return FAILURE;

		}

	printf("Eneter val: ");
	scanf(" %d",&val);

	que_t *_tmp = start,*prev=NULL;
loop:	while(_tmp && _tmp->data != val){//when it fails(comes out of loop) the _tmp value points to where the dup node present..
		
		prev = _tmp;
		_tmp = _tmp->next;
		
		}

	if(_tmp){	
		cnt++;

		if( cnt>1){//dup of give ele found then..
		
				que_t *tmp = _tmp;
				prev->next = tmp->next;
				free(tmp);
				_tmp = _tmp -> next;
				goto loop;
			}
		prev = _tmp;	
		_tmp = _tmp->next;
		goto loop;
		}

	if(cnt<2){//no dup of given ele found then..
		errno = ENODUP;
		return FAILURE;
		}

	return (errno = SUCCESS);


}

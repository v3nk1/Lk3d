//I hav removed the errors in ../ directory.. And also removed unusable variables(passing of que_t) here..
	//In this user can have only one single linked list..

#include<malloc.h>
#include<limits.h>   //for macro INT_MIN..

#include"error.h"

typedef struct queue{

	int data;
	struct queue *next;

	}que_t;

/*
	Its also no need..

int que_init(que_t *_p_que){

	bzero(_p_que,sizeof(*_p_que));

	return (errno = SUCCESS);

}*/

que_t *start;  //to hav reference of starting of que, peminantly..(throughout this process)

/*********************************************** INSERTION FUNCTIONS ***********************************************************/

int insert_last(void){ 

	int val;
	printf("enter the element u want to enque:");
	scanf(" %d",&val);

	que_t *_new; 

	_new = malloc(sizeof(que_t));
			if(!_new){
				errno = EMALL; 
				return FAILURE;
			  }

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

int insert_first(void){
	
	int val;
	printf("enter the element u want to enque: ");
	scanf(" %d",&val);
	
	que_t *_new;
	
	_new = malloc(sizeof(que_t));
	if(!_new){
		errno = EMALL;
		return FAILURE;
		}
	
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

int insert_bulk(void){

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
			if(insert_first()==-1){
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
                        if(insert_last()==-1){
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

/*********** mid ele*********/

que_t *midele(void){

	que_t *alt,*seq;
	alt=seq=start;
	while(alt && alt->next){
		seq = seq->next;
		alt = alt-> next->next;
		}
	return seq;
}

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

/******************************************************  SORTING A LIST  *******************************************************/

int sort_list_asc(void){//ascending order

        if(!start){//if list is empty
                errno = EEPTY;
                return FAILURE;
                }

        que_t *tmp = start;
        while(tmp->next){//if list has >1 elements  (it fails if list has only one element since "tmp->next = NULL")

                que_t *_tmp = start;

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


int sort_list_desc(void){//descending order

        if(!start){//if list is empty
                errno = EEPTY;
                return FAILURE;
                }

        que_t *tmp = start;
        while(tmp->next){//if list has >1 elements  (it fails if list has only one element since "tmp->next = NULL")

                que_t *_tmp = start;

                while(_tmp->next){
                        if(_tmp->data <  _tmp->next->data){
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



/******************************************************  DISPLAY FUNCTIONS *****************************************************/

/*displays list as is */
int disp_que(void){  //when printing think that we are inserting ele from right to left direction,

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
void find_max_min(int *max,int *min);
int disp_list_asc(void){

	que_t *tmp = start;
	if(!tmp){//for empty list..
		errno = EEPTY;
		return FAILURE;
		}
	
	if(!tmp->next){//for one element list..
		return (errno = SUCCESS);
		}

	int prev_swap=INT_MIN;// for this include<limits.h>
	int min,max;
	find_max_min(&min,&max);

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

void find_max_min(int *min,int *max){

	que_t *tmp = start;
	
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

int disp_list_dsc(void){

	que_t *tmp = start;	
	
	if(!tmp){//for empty list
		errno = EEPTY;
		return FAILURE;
		}

	if(!tmp->next){//for 1 ele list

		return (errno = SUCCESS);

		}
	
	int min,max;
	find_max_min(&min,&max);//if u invoke it at the start of the function then causes segmentation fault
	
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

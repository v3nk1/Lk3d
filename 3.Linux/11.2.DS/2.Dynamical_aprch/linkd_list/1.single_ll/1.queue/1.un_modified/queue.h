//through this ds: we can implement only one queue only(but in statical case its up to end user, user can create n num of queues in statical approach but here only one que), bcoz we have only one start variable of type ptr to que_t(the 1 start variable is usedhere to hold the starting address of one que), So what if user created onther queue we cannot hold it..
	//Actually in this approach user no need to create even single instance of any freaking que_t, so see the "correct" dir

#include<malloc.h>
#include"error.h"

typedef struct queue{

	int data;
	struct queue *next;

	}que_t;

int que_init(que_t *_p_que){

	bzero(_p_que,sizeof(*_p_que));

	return (errno = SUCCESS);

}

que_t *start;  //to hav reference of starting of que, peminantly..(throughout this process)
	//its initial position is NULL, so "if start is NULL que is empty".

int enque(que_t *_p_que,int val){ //que_t *_p_que is a dummy variable no need to pass. u can remove it here also..

	que_t *_new; 

	_new = malloc(sizeof(que_t));
			if(!_new){
				errno = EMALL; 
				return FAILURE;
			  }

/*case1: if the given ele is first ele of que*/
				
	if(!start){// This condition is true only if and only if start is NULL, means que is empty..
			
		start = _new; 	//to dont loose the reference of starting node..

		_new -> data = val;
		_new -> next = NULL; //to identify end of que..
		
		return SUCCESS; //if u doesnt give return here it exececute bellow code also ever if it success..

        	}
	

/*case2: if there is some elements already exists */

	if(start){
	
		que_t *prev = start;   //we are making a copy of start(after once an element has entered into Q) for every operation, if no element then start is obviously NULL.

		while(prev->next)    //very very importent..
			prev = prev->next;

		prev->next = _new;

		_new -> data = val;
		_new -> next = NULL;
		
		return SUCCESS;

	}
		
}

/*Always deletes the first element in the que */
int deque(que_t _que){//que_t _que is a dummy variable no need to pass. u can remove it here also..
	
	que_t *tmp = start;

	if(!tmp){//if u give here !tmp->next  even 1 elemet in the que it will execute and throws an error that que is empty.
		//if que is empty then tmp is NULL, Q is empty

		errno = EEPTY;
		return FAILURE;
		}

/*if que is not empty */	
	start = tmp->next;

	tmp->next = NULL;

	free(tmp);
	
return SUCCESS;	
	
}	

int disp_que(que_t que){

	que_t *tmp = start;

	if(!tmp){//if u give here !tmp->next  even 1 elemet in the que it will execute and throws an error that que is empty.
		errno = EEPTY;
		return FAILURE;
		}

	while(tmp){

		printf("%d ",tmp->data);
		tmp = tmp->next;
	}
	
	printf("\n");
	
return SUCCESS;

}

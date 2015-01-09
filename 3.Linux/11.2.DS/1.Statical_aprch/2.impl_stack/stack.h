#include"error.h"

#define MAX 100

typedef struct _stack{
	
		int _data[MAX];
		int _cnt;

	}stack_t;

int stack_init(stack_t *_p_stack){

	bzero(_p_stack,sizeof(*_p_stack));

	return (errno = SUCCESS);

} 

/*I considered that 0 index is top and MAX is bottom */
/*push always pushes given elemt into top of stack(ie., 0th index).. Stack follows rule: LIFO */
int push(stack_t *_p_stack,int val){ //for this it must be "call by reference" we are updating the existed stack

	if(_p_stack->_cnt == MAX){
			 errno = EFULL; 
			 return FAILURE;
			}

/*If u want to move the stack ele's inorder to empty the zero offset*/

/*************
 *  METHOD1  *
 *************/

	/* From 0th ele to last, it may complicated bcoz we hav to bother for 2 ele at a time */

/*	int i,tmp = _p_stack->_data[0]; //Or use 0th ele of that array as an tmp variable
		//tmp is used for backup variable for next iteration

	for(i=1;i<=_p_stack->_cnt;i++){
		int local=_p_stack->_data[i];
			//local is for backup variable until tmp job done;
		_p_stack -> _data[i] = tmp;
		tmp = local;
		}
*/

/*************
 *  METHOD2  *
 *************/

	/* From last ele; it may simpler than abv, since we just bother abt 1 ele*/

/*	int i;
	for(i=_p_stack->_cnt-1;i>=0;i--)
		_p_stack->_data[i+1]=_p_stack->_data[i];
*/

/*************
 *  METHOD3  *
 *************/
	
	/*Moving cnt*4 bytes from 0th offset to 1 offset & then override 0th element*/
	memcpy(_p_stack->_data+1,_p_stack->_data,_p_stack->_cnt*4);


	_p_stack -> _data[0] = val;
	_p_stack -> _cnt++;	

	return (errno = SUCCESS);

}

/*pop always deletes the top ele of stack (so 0th ele of stack)*/
int pop(stack_t *_p_stack){ //for this it must be "call by reference" we are updating the existed stack

	if(!(_p_stack->_cnt)){
			errno = EEPTY;
			return FAILURE;
			}
	int _i=0;
	for(;_i<_p_stack->_cnt-1;_i++){

			_p_stack -> _data[_i] = _p_stack -> _data[_i+1];
			
		}
	_p_stack -> _cnt--;
	return SUCCESS;

}

/*peek returns the element on the top of stack(ie., 0)*/
int peek(stack_t _p_stack){ //to peek no need of "call by reference" just do "call by value", since we are not updating any data in this function

	if(!(_p_stack._cnt)){
                        errno = EEPTY;
                        return FAILURE;
                        }
	return _p_stack . _data[0];

}

/*display stack from top to bottom*/
int disp_stack(stack_t _stack){ //to display no need of "call by reference" just do "call by value", since we are not updating any data in this function

	if(!(_stack._cnt)){
                        errno = EEPTY;
                        return FAILURE;
                        }
	int _i=0;
	for(;_i<_stack._cnt;_i++){

		printf("%d ",_stack._data[_i]);

		}
	printf("\n");

	return SUCCESS;

}

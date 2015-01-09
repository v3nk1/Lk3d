
#include<stdio.h>
#include<string.h>

//#include"perror.h"  //redifinition of my_errmsg  error will thrown by compiler..
extern int errno;

#define SUCC 0

#define FAIL (-1)
#define EFULL -2
#define EEPTY -3
#define EPOL -4
#define EMAX -5

#define MAX 123

#define FQ_FIFO 100


typedef struct fqueue{ //fqueue means fifo que

	int _que[MAX];
	int _policy;
	int _cnt ; //cnt = garbage value
	
	}fque_t; //user must create fque_t instance to create my function


typedef struct fque_attr{
	
	int max;    //for user defined value
	int policy; //FIFO or LIFO
	
	}fque_attr_t;


int fque_attr_init(fque_attr_t * _fqattr){	//initialises to default values
	
		_fqattr -> max = MAX;
		_fqattr -> policy = FQ_FIFO;
		
		return (errno = SUCC);
	}


/*set the size of Q by user as required*/
int fque_attr_setmax(fque_attr_t *_fqattr,int max){  //ignored(limitation)
	
	if(max > 0 && max <= MAX){ 

		_fqattr -> max = max;
		return (errno = SUCC);

		}
	else 
		return (errno = EMAX);
		
}

/*set the policy of Q by user as required*/
int fque_attr_setpolicy(fque_attr_t *_fqattr,int policy ){// ignored(limitation)

	if(policy == FQ_FIFO ){

		_fqattr -> policy = policy;	
		return (errno = SUCC);

		}

	else return (errno = EPOL);

	}

/*get the fque current attributes*/
int fque_getattr(fque_t *_fque,fque_attr_t *_attr){
	
		_attr -> max = MAX;
		_attr -> policy = FQ_FIFO;

	return SUCC;
}

/*initialization of a que*/
int fque_init(fque_t *_fque,fque_attr_t *_fqattr){

	
	if(_fqattr == NULL){
	
		_fque -> _que[MAX]; 
		_fque -> _policy = FQ_FIFO;
		_fque -> _cnt = 0;
		//backup();

	}
	else{
		_fque -> _que[ _fqattr -> max]; //it is doubt..................
		_fque -> _cnt = 0;
		_fque -> _policy = _fqattr -> policy;
		
		}
	return (errno = SUCC);
}

/*distroy the que attribute*/
int fque_attr_distroy(fque_attr_t *fqattr){

	memset(fqattr,0,sizeof(*fqattr));

	return (errno = SUCC);
}

/*flush the que to empty and by filling all ele to 0's*/
int fque_flush(fque_t *_fque){

	memset(_fque,0,sizeof(*_fque));
	
	return (errno = SUCC);

}

/*enter(push) an ele into a que*/
int enque(fque_t *tmp,int val){

	if(tmp -> _cnt > 99)
		return EFULL;
	else{

	tmp -> _que[tmp->_cnt] = val;
	tmp -> _cnt++;
	return (errno = SUCC);
	}
	
}
		
/*delete an element from a que*/
int deque(fque_t *tmp){

	if(tmp->_cnt >0){

	int i;
	for(i=0;i<(tmp->_cnt-1);i++){
		tmp -> _que[i] = tmp -> _que[i+1];
		}
	tmp -> _cnt --;
	return (errno = SUCC);

	}

	else return (errno = EEPTY);

}

/*print the present elements in a que*/
int print_que(fque_t *_fque){

	if(_fque -> _cnt == 0) return (errno = EEPTY);
	int i;
	for(i=0;i< (_fque -> _cnt) ; i++){

		printf("%d ",_fque -> _que[i]);
	}
	printf("\n");
	return (errno = SUCC);
}

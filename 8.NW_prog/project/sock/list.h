#include<stdio.h>
#include<malloc.h>

typedef struct queue{
	char data[20];//data = cname
	char buff[1024];
	lock_t lck;
        int msgcnt;
	int rcv;
	int snd;
	struct queue *next;
	}que_t;

que_t *start;

int insert(que_t **_list,char *cmname){ 

	que_t *_new;
	_new = malloc(sizeof(que_t));
			if(!_new){
				perror("malloc"); 
				return -1;
			  }
	if(!start){
		start = _new; 
		strcpy(_new -> data,cmname);
		_new -> next = NULL;
		return 0;
        	}

	if(start){
		que_t *prev = start;
		while(prev->next)   
			prev = prev->next;
		prev->next = _new;
		strcpy(_new -> data,cmname);
		_new -> next = NULL;
		return 0;
	}
}

int del_ele(que_t **_list,char *cmname){

	que_t *tmp = start;
	if(!tmp)
		return -1;
	if(!strcmp(tmp -> data,cmname)){
			start = tmp -> next;
			free(tmp);
			return 0;
			}
	que_t *prev;
	while(strcmp(tmp->data,cmname)){
				prev = tmp;
				if(!tmp->next)
					return -1;
				tmp = tmp->next;
				}
	prev -> next = tmp->next;
	free(tmp);
	return 0;
}

que_t *search(que_t **_list,char *cmname){

	que_t *tmp = start;
	if(!tmp)
		return NULL;
	if(!strcmp(tmp -> data,cmname))
				return tmp;
	que_t *prev;
	while(strcmp(tmp->data,cmname)){
				prev = tmp;
				if(!tmp->next)
					return NULL;
				tmp = tmp->next;
			}
	return tmp;

}

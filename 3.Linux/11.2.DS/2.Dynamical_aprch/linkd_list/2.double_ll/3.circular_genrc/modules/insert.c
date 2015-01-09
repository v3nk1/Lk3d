
#include <malloc.h>
#include <string.h>
#include "../headers/dcll_gen.h"
#include "../headers/errno.h"

int insert_first(dcll_t *dcll,void *data,char *disc){
			//disc is for storing discription of that type, its bcoz		\
			of identification and we are using geniric type

	dcll_t new;
	new = malloc(sizeof(dcll_t));
	if(!new){
		errno = EMALLOC;
		return FAILURE;
		}
	
	cnt++;
	
	new->idno = cnt;
	strcpy(new->node_disc,disc);
	new->dptr = data;
	new->prev = NULL;
	
	if(*dcll){
		new->next = *dcll;
		(*dcll)->prev = new;
		}
		
	*dcll=new;
	
	return SUCCESS;

}

int insert_last(dcll_t *dcll,void *data,char *disc){

	dcll_t new,*tmp;

	new = malloc(sizeof(dcll_t));
	if(!new){
		errno = EMALLOC;
		return FAILURE;
		}
	
	cnt++;
	
	new->idno = cnt;
	strcpy(new->node_disc,disc);
	new->dptr = data;
	new->next = NULL;

	if(!*dcll){
		*dcll=new;
		return SUCCESS;
		}

	tmp = dcll;
	while(*tmp)
		(*tmp)=(*tmp)->next;

	new->prev = *tmp;
	(*tmp)->next = new;

	return SUCCESS;
}

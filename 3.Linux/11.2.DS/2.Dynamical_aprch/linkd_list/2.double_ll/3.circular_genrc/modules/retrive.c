#include "../headers/dcll_gen.h"
#include "../headers/errno.h"

void *retrive(dcll_t dcll,nodeid idno){

	if(!dcll){
		errno = EEMPTY;
		return NULL;
		}

	while(dcll && dcll->idno != idno)
				dcll=dcll->next;
	if(dcll)
		return dcll->dptr;
	
	errno = ENOTFND;
	return NULL;

}

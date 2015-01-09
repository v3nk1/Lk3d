#include "../headers/dcll_gen.h"
#include "../headers/errno.h"

int print_id(dcll_t dcll){

	if(!dcll){
		errno = EEMPTY;
		return FAILURE;
		}

	while(dcll){
		printf("\t\t\t\t\tid: %3d, disc: %s\n",dcll->idno,dcll->node_disc);
		dcll=dcll->next;
		}
	return (errno = SUCCESS);
}

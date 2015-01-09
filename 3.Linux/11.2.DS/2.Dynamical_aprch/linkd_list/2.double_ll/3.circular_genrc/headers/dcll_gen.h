/*Double circular linked list header*/

#ifndef _DCLL_H

#define _DCLL_H

typedef unsigned int nodeid;
int cnt;

typedef struct dcll_list {
	
		nodeid idno;
		char node_disc[100];
		struct dcll_list *prev;
		void *dptr;		/*Data pointer given by user*/
		struct dcll_list *next;

		}*dcll_t;

void dcll_init(dcll_t *dcll);
int insert_first(dcll_t *dcll,void *data,char *disc);
int insert_last(dcll_t *dcll,void *data,char *disc);
int print_id(dcll_t dcll);
//extern void *retrive(dcll_t,nodeid); or
void *retrive(dcll_t,nodeid);

#endif

//it maitains node headers of a particular list

#ifndef _HEADERS

#define HEADERS

#include<stdio.h>
#include<malloc.h>
#include<limits.h>   //for macro INT_MIN..

#include"lheaders.h"
#include"errno.h"

typedef struct queue{

	int data;
	struct queue *next;

	}que_t;

que_t *start;  //to hav reference of start of the list

extern void menuHandler(char);

extern void del_menu(void);
extern int del_hand(list_t *);
extern int del_first(list_t **);
extern int del_last(list_t **);
extern int del_ele(list_t **);
extern int flush(list_t **);


extern void insert_menu(void);
extern void insert_bulk_menu(void);
extern int insert_hand(list_t *);
extern int insert_last(list_t **);
extern int insert_first(list_t **);
extern int insert_bulk(list_t **);

extern void disp_menu(void);
extern int disp_hand(list_t *);
extern int disp_que(list_t *);
extern int disp_list_asc(list_t *);
extern int disp_list_dsc(list_t *);
extern int disp_list_rev(list_t *);

extern void sort_list_menu(void);
extern int sort_hand(list_t *);
extern int sort_list_asc(list_t **);
extern int sort_list_desc(list_t **_list);


#endif

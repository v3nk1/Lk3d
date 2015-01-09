#ifndef _HEADERS

#define HEADERS

#include<stdio.h>
#include<malloc.h>
#include<limits.h>   //for macro INT_MIN..

extern void menuHandler(char);

extern void del_hand(void);
extern void del_menu(void);
extern int del_first(void);
extern int del_last(void);
extern int del_ele(void);
extern int flush(void);
extern int del_all_dups(void);
extern int del_ele_dups(void);

extern void insert_hand(void);
extern void insert_menu(void);
extern int insert_last(void);
extern int insert_first(void);
extern int insert_bulk(void);
extern void insert_bulk_menu(void);

extern void disp_hand(void);
extern void disp_menu(void);
extern int disp_que(void);
extern int disp_list_asc(void);
extern int disp_list_dsc(void);
extern int disp_list_rev(void);

extern void sort_hand(void);
extern void sort_list_menu(void);
extern int sort_list_asc(void);
extern int sort_list_desc(void);


typedef struct queue{

	int data;
	struct queue *next;

	}que_t;

que_t *start;  //to hav reference of starting of que, peminantly..(throughout this process)

#endif

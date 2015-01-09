//it maitains list headers

#ifndef LHEAD
	
#define LHEAD

typedef struct node{//for storing list entities..
        int lno;        // list no
        char lname[19]; //list name
        struct queue *lstart; //to hold starting node of the list
        int cnt;// node count in a particular list..
        struct node *lnext; //to hold ref of next list if any..
        }list_t;

list_t *l1st; //to hold reference of 1st list among the bunch of lists..
list_t *lcurr;//to hold the ref of current list..

int cnt;     //to maintain how many list are present, and give numbering to the lists..

extern void node_list_menu(void);
extern list_t *node_list_menuHandler(void);

extern void list_menu(void);
extern void list_hand(void);
extern int add_list(void);
extern int del_list(void);
extern int disp_lists(void);
extern int curr_list(void);
extern int change_curr_list(void);


#endif

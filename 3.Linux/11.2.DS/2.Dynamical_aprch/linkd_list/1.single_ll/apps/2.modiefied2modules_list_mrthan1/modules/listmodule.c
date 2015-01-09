
#include<stdio.h>
#include<strings.h>
#include<malloc.h>

#include"../headers/nheaders.h"
#include"../headers/errno.h"
#include"../headers/lheaders.h"

extern struct queue *lstart;

int del_list_by_no(void){
				int no;
                                printf("Enter list id_no: ");
                                scanf(" %d",&no);
                                list_t *prev=l1st,*tmp = l1st;
				
				if(tmp->lno == no){//if the deleted list is first list
						l1st = tmp->lnext;
						cnt--;
						if(no == lcurr->lno) lcurr = l1st;//if u hav deltd a node,lcurr is also pointing  to that node only then it will be pointed to some garbage(junk) values, So we are updating "lcurr to l1st" if u've deletd node hoding by lcurr.
			     			printf("Deleted_list: id(%d), name(%s)\n\n",tmp->lno,tmp->lname);
						free(tmp);
						return (errno = SUCCESS);
						}
				tmp = tmp->lnext;				

                                while(tmp && tmp->lno != no ){
                                                prev = tmp;
                                                tmp = tmp->lnext;
                                                }
				
                                if(tmp){//if the deleted list is last or middle list
					if(no == lcurr->lno) lcurr = l1st;
                                        prev->lnext = tmp->lnext;
			     		printf("Deleted_list: id(%d), name(%s)\n\n",tmp->lno,tmp->lname);
                                        free(tmp);
					cnt--;
					if(cnt==0) l1st = NULL;
                                        return (errno = SUCCESS);
                                        }
                                errno = ENFND;
                                return FAILURE;

}

int del_list_by_name(void){
		
	char name[19];
	printf("Enter the exact name of the list: ");
	scanf(" %[^\n]",name);
	
	list_t *prev=l1st,*tmp = l1st;

	if(!strcmp(tmp->lname,name)){//if the deleted list is first list
                             l1st = tmp->lnext;
			     if(!strcmp(name,lcurr->lname)) lcurr = l1st;
                             cnt--;
			     printf("Deleted_list: id(%d), name(%s)\n\n",tmp->lno,tmp->lname);
                             free(tmp);
                             return (errno = SUCCESS);
                             }
                   tmp = tmp->lnext;

        while(tmp && strcmp(tmp->lname,name) ){
                                    prev = tmp;
                                    tmp = tmp->lnext;
                                    }
        if(tmp){
	     if(!strcmp(name,lcurr->lname)) lcurr = l1st;
             prev->lnext = tmp->lnext;
	     printf("Deleted_list: id(%d), name(%s)\n\n",tmp->lno,tmp->lname);
             free(tmp);
	     cnt--;
             return (errno = SUCCESS);
               }
        errno = ENFND;
        return FAILURE;

}

void list_init(list_t **list){

	bzero(*list,sizeof(**list));

}
	
int add_list(void){// add/create new list

	cnt++;

	list_t *nw_list = malloc(sizeof(struct node));
		if(!nw_list){
			errno = EMALL;
			return FAILURE;
			}
	list_init(&nw_list);
	
	printf("Enter the name of the list: ");
	scanf(" %[^\n]",nw_list->lname);// i'm changing the delimit of scanf if u use %s no spaces are allowed, so i've used it instead of "%s" to read upto '\n'(ie., upto press enter(we can say it new line staring only na..))
	nw_list->lno = cnt;
	
	if(!l1st){
		l1st = nw_list;
		nw_list->lnext = NULL;
		lcurr=nw_list;
		return (errno = SUCCESS);
		}
		
	list_t *lprev,*tmp = l1st;
	while(tmp){//always insert last fasion..
		lprev = tmp;
		tmp = tmp->lnext;
		}
	lprev->lnext = nw_list;
	lcurr = nw_list;
	nw_list->lnext = NULL;

	return (errno = SUCCESS);

}

int del_list(void){

	if(!l1st){
		errno = ENOLIST;
		return FAILURE;
		}

	char cho;

	while(1){
		del_list_menu();
		printf("Enter the choice of deletion: ");
		scanf(" %c",&cho);
		
		switch(cho){
			
			case '1':
				if(del_list_by_no()==-1) errmsg("del_list_by_no");
				break;
				
			case '2':
				if(del_list_by_name()==-1) errmsg("del_list_by_name");
				break;
				
			case '0':	return;
			case 'x':	return;
			case 'X':	return;

			default:
				printf("No such option\n");
				continue;
			}

		}


}

int disp_lists(void){

	printf("\n");

	list_t *tmp = l1st;
	if(!tmp){
		errno = ENOLIST;
		return FAILURE;
		}

	printf("\n");
	printf("\t\t\t\t\t               ALL_LISTS(%d)\n",cnt);
        printf("\t\t\t\t\t==============================================\n");
        printf("\t\t\t\t\t|   List_id(nodes) |     List_name           |\n");
        printf("\t\t\t\t\t==============================================\n");

while(tmp){
		
        printf("\t\t\t\t\t|%7d(%d)	   |     %-20s|\n",tmp->lno,tmp->cnt,tmp->lname);
	if(tmp->lnext)
        printf("\t\t\t\t\t``````````````````````````````````````````````\n");
	tmp = tmp->lnext;
	
	}

        printf("\t\t\t\t\t==============================================\n");
	printf("\n\n\n");

	return (errno = SUCCESS);

}


int curr_list(void){

	if(!lcurr){
		errno = ENOLIST;
		return FAILURE;
		}

	printf("list id: %d, list_name: %s, total_nodes_in_list: %d\n\n",lcurr->lno,lcurr->lname,lcurr->cnt);
	return (errno = SUCCESS);

}	

int change_curr_list(void){

	if(!l1st){
		errno = ENOLIST;
		return FAILURE;
		}

	if(!l1st->lnext){
		errno = E1LIST;
		return FAILURE;
		}
	int no;
	printf("Enter lid u want 2 change to: ");
	scanf(" %d",&no);
		
	list_t *prev=l1st,*tmp = l1st;
	while(tmp && tmp->lno != no){
			tmp = tmp->lnext;
			}
	if(tmp){
		lcurr = tmp;	
		return (errno = SUCCESS);
		}	

	errno = ENFND;
	return FAILURE;

}


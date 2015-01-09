#include<stdio.h>
#include"../headers/errno.h"
#include"../headers/lheaders.h"

//extern void list_hand(void);

int _id;
char _name[19];

list_t *find_ref_of_lid(void){

	list_t *tmp = l1st;
	if(!tmp){
		errno = ENOLIST;
		return (list_t *)FAILURE;
		}

	while(tmp && tmp->lno != _id){
		tmp = tmp->lnext;
		}
	if(tmp){
		return tmp;
		}
	
	errno = ENFND;
	return (list_t *)FAILURE;

}

list_t *find_ref_of_lname(void){

        list_t *tmp = l1st;
        if(!tmp){
                errno = ENOLIST;
                return (list_t *)FAILURE;
                }

        while(tmp && strcmp(tmp->lname,_name)){
                tmp = tmp->lnext;
                }
        if(tmp){
                return tmp;
                }
        
        errno = ENFND;
        return (list_t *)FAILURE;


}


list_t *node_list_menuHandler(void){

	if(!l1st ){
		errno = ENOLIST;
		return (list_t *)FAILURE;
		}

	list_t *ret;

	char cho;

while(1){

	node_list_menu();
	printf("Enter ur choice: ");
	scanf(" %c",&cho);
	
	if(cho == '1'){
		return lcurr;
		}
	if(cho == '2'){
		printf("Enter list_id: ");
		scanf(" %d",&_id);
		if((ret = find_ref_of_lid())==((list_t*)-1)){
				errmsg("find_ref_node");
				continue;
				}
		return ret;
		}
	if(cho == '3'){
		printf("Enter list_name: ");
		scanf(" %[^\n]",_name);
		if((ret =find_ref_of_lname())==((list_t *)-1)){
				errmsg("find_ref_node");
				continue;
				}
		return ret;
		}

	if(cho == '4'){
		list_hand();
		continue;
		}

	if(cho == '0'||cho =='x'||cho=='X') return;	

	else{
		printf("No such option\n");
		continue;
 		}

    }

}

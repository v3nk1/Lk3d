#include<stdio.h>
#include"../headers/nheaders.h"
#include"../headers/lheaders.h"
//#include"../headers/error.h"

void menuHandler(char ch){

                if( ch == 'i' || ch == 'I'){
					if(insert_hand(node_list_menuHandler())==-1)
								errmsg("insert_hand");
								if(!lcurr){//if no lists then it'll take the control to list_hand to give us a chance to add a list..
									printf("\n");
									list_hand();
									}
					return;
					}

                if( ch == 'd' || ch == 'D'){
					if(del_hand(node_list_menuHandler())==-1) errmsg("del_hand");	
					return;
					}

                if( ch == 's' || ch == 'S'){
					if(sort_hand(node_list_menuHandler())==-1) errmsg("sort_hand");
					return;
					}

                if( ch == 'l' || ch == 'L'){
					list_hand();
					return;
					}

                if( ch == 'p' || ch == 'P'){
					if(print_hand(node_list_menuHandler())==-1) errmsg("print_hand");
					return;
					}

		else{
                        printf("No such operation\n");
                        return;
                        }


}

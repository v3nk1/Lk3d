#include<stdio.h>
#include"../headers/nheaders.h"
//#include"../headers/error.h"

		int sort_hand(list_t *_list){

                                if(_list==(list_t *)-1){
							errno=ENOLIST;
                                                        return FAILURE;

                                                }



                                                while(1){
                                                        sort_list_menu();
                                                        int tmp;
                                                        printf("enter your choice(sort): ");
                                                        scanf(" %d",&tmp);
                                                        if(tmp == 1){
                                                                if(sort_list_asc(&_list)==-1) errmsg("sort_list_asc");
                                                                continue;//if u give break here then then it comes out of the sort_list_menu, if u give return it goes to main_menu, if u give continue then it will execute again from while(1) sort_list_menu..
			// and most importnt is if u invoke call by value then no saving of result is done, make sure that it will be call by reference.. 
                                                                }
                                                        if(tmp == 2){
                                                                if(sort_list_desc(&_list)==-1) errmsg("sort_list_desc");
                                                                continue;
                                                                }
                                                        if(tmp == 0) break;
                                                        else{
                                                                printf("Invalid choice\n");
                                                                continue;
                                                                }
                                                }
                                                return;
                                        }


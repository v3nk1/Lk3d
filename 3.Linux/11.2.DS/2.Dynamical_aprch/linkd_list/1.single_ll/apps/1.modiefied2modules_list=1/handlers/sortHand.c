#include<stdio.h>
#include"../headers.h"
//#include"../error.h"

	void sort_hand(void)		{
                                                while(1){
                                                        sort_list_menu();
                                                        int tmp;
                                                        printf("enter your choice(sort): ");
                                                        scanf(" %d",&tmp);
                                                        if(tmp == 1){
                                                                if(sort_list_asc()==-1) errmsg("sort_list_asc");
                                                                continue;//if u give break here then then it comes out of the sort_list_menu, if u give return it goes to main_menu, if u give continue then it will execute again from while(1) sort_list_menu..
                                                                }
                                                        if(tmp == 2){
                                                                if(sort_list_desc()==-1) errmsg("sort_list_desc");
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


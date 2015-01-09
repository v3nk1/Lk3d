#include<stdio.h>
#include"../headers/nheaders.h"
//#include"../headers/error.h"

int print_hand(list_t *_list){

                                if(_list==(list_t *)-1){
							errno=ENOLIST;
                                                        return FAILURE;

                                                }


	                                        while(1){
                                                disp_menu();
                                                int tmp;
                                                printf("enter your disp choice: ");
                                                scanf(" %d",&tmp);
                                                if(tmp == 1){
                                                        if(disp_que(_list)==-1) errmsg("disp_Q");
                                                        continue;
                                                        }
                                                if(tmp == 2){
                                                        if(disp_list_asc(_list)==-1) errmsg("disp_list_asc");
                                                        continue;
                                                        }
                                                if(tmp == 3){
                                                        if(disp_list_dsc(_list)==-1) errmsg("disp_list_dsc");
                                                        continue;
                                                        }
						if(tmp == 4){
							if(disp_list_rev(_list)==-1) errmsg("disp_list_rev");
							continue;
							}
                                                if(tmp == 0) break;

                                                else{
                                                        printf("Invalid choice\n");
                                                        continue;
                                                        }
                                                }
                         }

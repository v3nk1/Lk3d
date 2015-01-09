#include<stdio.h>
#include"../headers.h"
//#include"../error.h"

void print_hand(void){

	                                        while(1){
                                                disp_menu();
                                                int tmp;
                                                printf("enter your disp choice: ");
                                                scanf(" %d",&tmp);
                                                if(tmp == 1){
                                                        if(disp_que()==-1) errmsg("disp_Q");
                                                        continue;
                                                        }
                                                if(tmp == 2){
                                                        if(disp_list_asc()==-1) errmsg("disp_list_asc");
                                                        continue;
                                                        }
                                                if(tmp == 3){
                                                        if(disp_list_dsc()==-1) errmsg("disp_list_dsc");
                                                        continue;
                                                        }
						if(tmp == 4){
							if(disp_list_rev()==-1) errmsg("disp_list_rev");
							continue;
							}
                                                if(tmp == 0) break;

                                                else{
                                                        printf("Invalid choice\n");
                                                        continue;
                                                        }
                                                }
                         }

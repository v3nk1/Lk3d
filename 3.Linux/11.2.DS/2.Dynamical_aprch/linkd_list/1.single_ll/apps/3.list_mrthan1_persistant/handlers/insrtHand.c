#include<stdio.h>
#include"../headers/nheaders.h"
#include"../headers/error.h"
		
		int insert_hand(list_t *_list){

                                if(_list==(list_t *)-1){
							errno=ENOLIST;
                                                        return FAILURE;
                                                }

				        int tmp;
                                        while(1){
                                        
                                                insert_menu();
                                                printf("enter ur choice no:");
                                                scanf(" %d",&tmp);
                                                
                                                switch(tmp){
                                                
                                                        case  1:
                                                                        if(insert_first(&_list)==-1) errmsg("insert_first");
                                                                        return;
                                                        case  2:        
                                                                        if(insert_last(&_list)==-1) errmsg("insert_last");
                                                                        return;
                                                        case  3:
                                                                        if(insert_bulk(&_list)==-1) errmsg("insert_bulk");
                                                                        return;

                                                        case  0:     /*come out of insert loop(menu)*/
                                                                        {//braces must and shud otherwise error..
                                                //since in switch cases: only one statement is allowed..
                                                                        char ext;
                                                                        printf("Are sure exit to main menu [y/n]: ");
                                                                        scanf(" %c",&ext);
                                                                        if(ext == 'y' || ext == 'Y')
                                                                                                        return;
                                                                        if(ext == 'n' || ext == 'N')
                                                                                                        continue;
                                                                        else
                                                                                continue;
                                                                        }

                                                        default:
                                                                        printf("No such insert option\n");
                                                                        return;

                                                                        }

                                                }
                                        
		}

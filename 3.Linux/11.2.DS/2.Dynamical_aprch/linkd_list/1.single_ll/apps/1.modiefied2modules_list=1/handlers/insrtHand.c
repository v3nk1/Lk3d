#include<stdio.h>
#include"../headers.h"
#include"../error.h"
		void insert_hand(void){
				        int tmp;
                                        while(1){
                                        
                                                insert_menu();
                                                printf("enter ur choice no:");
                                                scanf(" %d",&tmp);
                                                
                                                switch(tmp){
                                                
                                                        case  1:
                                                                        if(insert_first()==-1) errmsg("insert_first");
                                                                        return;
                                                        case  2:        
                                                                        if(insert_last()==-1) errmsg("insert_last");
                                                                        return;
                                                        case  3:
                                                                        if(insert_bulk()==-1) errmsg("insert_bulk");
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

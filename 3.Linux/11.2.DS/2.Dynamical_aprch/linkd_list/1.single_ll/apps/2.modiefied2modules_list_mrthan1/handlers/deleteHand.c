#include<stdio.h>
#include"../headers/nheaders.h"
//#include"../error.h"

int del_hand(list_t *_list){
				if(_list==(list_t *)-1){
							errno = ENOLIST;
							return FAILURE;
						}

                                        int tmp;
                                        while(1){

                                                del_menu();
                                                printf("enter ur choice no:");
                                                scanf(" %d",&tmp);

                                                switch(tmp){

                                                        case  1:        /*fifo*/
                                                                        if(del_first(&_list)==-1) errmsg("del_first");
                                                                        return;
                                                        case  2:        /*lifo*/
                                                                        if(del_last(&_list)==-1) errmsg("del_last");
                                                                        return;
                                                        case  3:
                                                                        if(del_ele(&_list)==-1) errmsg("del_ele");
                                                                        return;

                                                        case  4:     /* flush all*/
                                                                        {//braces must and shud otherwise error..
                                                //since in switch cases: only one statement is allowed..
                                                                        char flsh;
                                                                        printf("Are sure total data will lost [y/n]: ");
                                                                        scanf(" %c",&flsh);
                                                                        if(flsh == 'y' || flsh == 'Y'){
                                                                                                        flush(&_list);
                                                                                                        return;
                                                                                               }

                                                                        if(flsh == 'n' || flsh == 'N')
                                                                                                        continue;
                                                                        else
                                                                                continue;
                                                                        }


                                                        case  0:     /*come out of del loop(menu)*/
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
                                                                        printf("No such del option\n");
                                                                        return;

                                                                        }


                                                }
                                        }

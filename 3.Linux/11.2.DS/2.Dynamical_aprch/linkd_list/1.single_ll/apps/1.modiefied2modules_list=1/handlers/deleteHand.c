#include<stdio.h>
#include"../headers.h"
//#include"../error.h"

void del_hand(void){

                                        int tmp;
                                        while(1){

                                                del_menu();
                                                printf("enter ur choice no:");
                                                scanf(" %d",&tmp);

                                                switch(tmp){

                                                        case  1:        /*fifo*/
                                                                        if(del_first()==-1) errmsg("del_first");
                                                                        return;
                                                        case  2:        /*lifo*/
                                                                        if(del_last()==-1) errmsg("del_last");
                                                                        return;
                                                        case  3:
                                                                        if(del_ele()==-1) errmsg("del_ele");
                                                                        return;

                                                        case  4:     /* flush all*/
                                                                        {//braces must and shud otherwise error..
                                                //since in switch cases: only one statement is allowed..
                                                                        char flsh;
                                                                        printf("Are sure total data will lost [y/n]: ");
                                                                        scanf(" %c",&flsh);
                                                                        if(flsh == 'y' || flsh == 'Y'){
                                                                                                        flush();
                                                                                                        return;
                                                                                               }

                                                                        if(flsh == 'n' || flsh == 'N')
                                                                                                        continue;
                                                                        else
                                                                                continue;
                                                                        }
							case 5:	
									if(del_all_dups()==-1) errmsg("del_all_dup");	
									return;
							case 6:
									if(del_ele_dups()==-1) errmsg("del_ele_dup");
									return;

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

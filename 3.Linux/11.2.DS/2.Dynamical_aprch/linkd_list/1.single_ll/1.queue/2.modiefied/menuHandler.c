#include<stdio.h>
#include"queue.h"

void menuHandler(char ch){

/* we cannt use switch becoz in switch cases char constants are not allowed

	switch(ch){

		case ch == 'e' || ch == 'E' :
						enque();
						break;

		case ch == 'd' || ch == 'D' :
						deque();
						break;

		case ch == 'p' || ch == 'P' :
						disp_que();
						break;
		default	:
			printf("No such operation\n");
			break;

	}
*/


                if( ch == 'e' || ch == 'E'){
							
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
									printf("No such del option\n");
									return;

									}	

						}
					}
						
                if( ch == 'd' || ch == 'D'){
						int tmp;
					while(1){

						del_menu();
						printf("enter ur choice no:");
						scanf(" %d",&tmp);
						
						switch(tmp){

							case  1:	/*fifo*/
									if(del_first()==-1) errmsg("del_first");
									return;
							case  2:	/*lifo*/
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

                if( ch == 's' || ch == 'S'){	
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
                if( ch == 'p' || ch == 'P'){
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

						if(tmp == 0) break;

						else{
							printf("Invalid choice\n");
							continue;
							}
						}
				}
		else{
                        printf("No such operation\n");
                        return;
			}

}

#include<stdio.h>
#include"../headers/lheaders.h"
//#include"../headers/error.h"

void list_hand(void){

	char tmp;
	while(1){
		list_menu();
		printf("enter your choice(list): ");
		scanf(" %c",&tmp);

		if(tmp == 'a' || tmp ==  'A'){
					if(add_list()==-1) errmsg("add_list");
					return;
					}
		if(tmp == 'd' || tmp ==  'D'){
                                        if(del_list()==-1) errmsg("del_list");
                                        return;
                                        }
		if(tmp == 'p' || tmp ==  'P'){
                                        if(disp_lists()==-1) errmsg("disp_lists");
                                        return;
                                        }
		if(tmp == 'c' || tmp ==  'C'){
                                        if(curr_list()==-1) errmsg("curr_list");
                                        return;
                                        }
		if(tmp == 'h' || tmp ==  'H'){
                                        if(change_curr_list()==-1) errmsg("change_list");
                                        return;
                                        }
		if(tmp == '0' || tmp ==  'x' || tmp == 'X'){
                                       	return;
                                        }
		else{
			printf("No such option\n");
			continue;
			}

	}

}

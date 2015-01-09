#include<stdio.h>
#include"headers.h"

void menuHandler(char ch){

                if( ch == 'e' || ch == 'E'){
					insert_hand();
					return;
					}
                if( ch == 'd' || ch == 'D'){
					del_hand();	
					return;
					}
                if( ch == 's' || ch == 'S'){
					sort_hand();
					return;
					}
                if( ch == 'p' || ch == 'P'){
					print_hand();
					return;
					}
		else{
                        printf("No such operation\n");
                        return;
                        }


}

#include<stdio.h>

void menu(void){
	
	printf("\t\t\t\t\t            MAIN_MENU\n");
	printf("\t\t\t\t\t==================================\n");
	printf("\t\t\t\t\t|    CODE       |     ACTION     |\n");
	printf("\t\t\t\t\t==================================\n");
	printf("\t\t\t\t\t|    e/E        |     enque      |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|    d/D        |     deque      |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|    s/S        |     sort_list  |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|    p/P        |     disp_list  |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|   0/x/X       |     exit       |\n");
	printf("\t\t\t\t\t==================================\n");

}

void del_menu(void){

	printf("\t\t\t\t\t           DELETE_MENU\n");
	printf("\t\t\t\t\t==================================\n");
	printf("\t\t\t\t\t|    CODE       |     ACTION     |\n");
	printf("\t\t\t\t\t==================================\n");
	printf("\t\t\t\t\t|      1        |     del_first  |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|      2        |     del_last   |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|      3        |     del_ele    |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|      4        |     del_all    |\n");
	printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|      5        |   del_all_dups |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      6        |   del_ele_dups |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
	printf("\t\t\t\t\t|      0        |  exit_del_menu |\n");
	printf("\t\t\t\t\t==================================\n");

}

void insert_menu(void){

	printf("\t\t\t\t\t           INSERT_MENU\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    CODE       |     ACTION     |\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|      1        |   insert_first |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      2        |   insert_last  |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      3        |   insert_bulk  |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      0        |exit_insert_menu|\n");
        printf("\t\t\t\t\t==================================\n");

}

void insert_bulk_menu(void){

	printf("\t\t\t\t\t         INSERT_BULK_MENU\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    CODE       |  TYPE OF INSRT |\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|      1        |   insert_first |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      2        |   insert_last  |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      0        | exit_bulk_menu |\n");
        printf("\t\t\t\t\t==================================\n");

}

void sort_list_menu(void){

        printf("\t\t\t\t\t         SORT_LIST_MENU\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    CODE       | TYPE OF SORT   |\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|      1        | acending_sort  |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      2        | desending_sort |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      0        | exit_sort_menu |\n");
        printf("\t\t\t\t\t==================================\n");

}

void disp_menu(void){

	printf("\t\t\t\t\t         DISPLAY_LIST_MENU\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    CODE       | TYPE OF DISP   |\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|      1        |  as is in list |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      2        |   acending     |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      3        |   desending    |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      4        |  reverse order |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      0        | exit_disp_menu |\n");
        printf("\t\t\t\t\t==================================\n");

}

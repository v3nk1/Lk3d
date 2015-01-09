#include<stdio.h>

void list_menu(void){

        printf("\t\t\t\t\t            LIST_MENU\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    CODE       |     ACTION     |\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    a/A        |     add_list   |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|    d/D        |     del_list   |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|    p/P        |     disp_lists |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|    c/C        |     curr_list  |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|    h/H        | change_currlist|\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|   0/x/X       |   exit_listMenu|\n");
        printf("\t\t\t\t\t==================================\n");

}

void node_list_menu(void){

        printf("\t\t\t\t\t         NODE_LIST_MENU\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    CODE       |     ACTION     |\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|      1        |     curr_list  |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      2        |     by list_id |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      3        |   by list_name |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      4        |  jump2list_menu|\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|   0/x/X       |   exit_listMenu|\n");
        printf("\t\t\t\t\t==================================\n");

}


void del_list_menu(void){

        printf("\t\t\t\t\t          DEL_LIST_MENU\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|    CODE       |    TYPE OF DEL |\n");
        printf("\t\t\t\t\t==================================\n");
        printf("\t\t\t\t\t|      1        |  by list id_no |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|      2        |  by list_name  |\n");
        printf("\t\t\t\t\t``````````````````````````````````\n");
        printf("\t\t\t\t\t|    0/x/X      |  exit_del_list |\n");
        printf("\t\t\t\t\t==================================\n");


}


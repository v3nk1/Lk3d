#include"list.h"

main(){

	if(del_last()==-1) errmsg("del_last");
	if(disp_list()==-1) errmsg("disp_list");
	if(sort_list()==-1) errmsg("sort_list");
	insert_first(5);
	sort_list();
	if(disp_list()==-1) errmsg("disp_list");
//	if(del_last()==-1) errmsg("del_last");
	insert_first(1);
	insert_first(2);
	insert_first(3);
	insert_first(4);
	insert_first(5);
	insert_first(6);
	insert_first(7);
	insert_first(8);
	insert_first(9);
	insert_first(10);
	if(disp_list()==-1) errmsg("disp_list");
	sort_list();
	if(disp_list()==-1) errmsg("disp_list");

}

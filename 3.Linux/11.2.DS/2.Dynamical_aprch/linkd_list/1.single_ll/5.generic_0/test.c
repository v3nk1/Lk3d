#include"list.h"

struct data{

	int temp;
	char str[10];

	}o={1234,"venkatesh"};

main(){

	list_t l1;
	list_init(&l1);

	char ch = 'A';

	insert_first(&l1,&ch);

	int i = 10;
	insert_first(&l1,&i);
	
	insert_first(&l1,&o);

	int *ri=NULL;
	char *rch=NULL;
//	read_list(l1,&rch);

	list_t tmp = l1;
	read_list(l1,&tmp);

	struct data rd;
//	rd.temp = ((struct data *)tmp->data)->temp;
//	strcpy(rd.str,((struct data *)tmp->data)->str);		//OR
	struct data *ptemp = tmp->data;
	rd.temp = ptemp->temp;
	strcpy(rd.str,ptemp->str);

	printf("temp = %i\n",rd.temp);
	printf("str = %s\n",rd.str);
	read_list(l1,&tmp);

	ri = tmp->data;
	printf("ri = %d\n",*ri);
	read_list(l1,&tmp);

	rch = tmp->data;
	printf("rch = %c\n",*rch);

	if(read_list(l1,&tmp)==-1) errmsg("read_list");
	if(read_list(l1,&tmp)==-1) errmsg("read_list");
	if(read_list(l1,&tmp)==-1) errmsg("read_list");
	if(read_list(l1,&tmp)==-1) errmsg("read_list");

}

#include<stdio.h>
struct data{
int i,*pi;
};//o={10,&o.i};
main(){
struct data o={10,&o.i};
printf("%d \n",o.i);
//struct data *pi=&o; //c here pi is ptr to struct data type..ie, ptr to structure.

//o.pi=&o.i;
//o.q=&o.i;
struct data *ptr=&o;
ptr->i=555;//(*ptr).i=1000;
printf("%d %d\n",(*ptr).i,*o.pi);//printf("%d \n",o.i); instead of (*ptr).i wecan use ptr->i ; all these print i value.
}


#include<stdio.h>
struct data{
	
	int a,b;

}o[2]={{1,2},{4,5}};

main(){
	
	int i;
	//struct data o[2];
	//o[0]={1,2};
	//o[1]={10,11};
	
	for(i=0;i<sizeof o/sizeof(struct data);i++){ // sizeof struct o , sizeof data , sizeof struct data = all r syntax errors;
                                             // sizeof o = sizeof(struct data); executes correctly
	printf("%d %d\n",o[i].a,o[i].b);}

}

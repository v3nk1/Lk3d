#include<stdio.h>

struct tag{
	int a;
	char ch;
	};

print(struct tag *obj,int n){

	int i;	
	for(i=0;i<n;i++)
		printf("%d, %c\n",obj[i].a,obj[i].ch);
}

main(){

	struct tag obj[10]={
			    [4]={40,'a'},
			    [8]={80,'b'}, 	/*Initialization of particular object in an array of obj */
			    [3].a=30		/*Init of particular member in an particular object in an array of obj */

				};
	print(obj,10);

}

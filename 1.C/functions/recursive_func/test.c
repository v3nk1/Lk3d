//guess output

#include<stdio.h>

int fun(int y){
	
	printf("=-> %d\n",y);
       	if(y)
		return fun(y/=10)*10+y%10;
	
        else
       		return 0;

}	      

main(){
      
          int n=657;
          printf(".....%d\n",fun(n));//*10+n%10);
 
}

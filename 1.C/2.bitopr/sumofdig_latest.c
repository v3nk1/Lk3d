//w.a.p for calculating the sum of the individual digits of entered decimal num;

#include<stdio.h>

#define pb pb_g

int sum_dig(unsigned long long int a){

	unsigned int b=0;
	int i=0;
/*	while(1){
		//pb(a&0xf,sizeof(unsigned long long int));
		
		b=b + (a & 0xf);
		//pb(b , sizeof (unsigned int));
		a=(a>>4);
		
		if(a==0) break;
		}
*/	while(1){
		
		if((a>>(4*i) & 0xf )== 0) break;
		b= b + (a>>4*i & 0xf);  // last bracket plays crutial role becoz of precedence 1st addition after only bitwise &.
		//pb(b , sizeof (unsigned int));
		
		
		i++;
		}
	return b;
}	

main(){

//unsigned int a;//it will limited to 8 digits only, after 8 unpridectble outputs will come.
	unsigned long long int a; // it is capable of storing 32 digits.
	printf("enter value: ");
	scanf("%llx",&a);
//printf("%lld\n",a);

	a=sum_dig(a);    // here a value is replaced by sum of individual digs. u dont want it declare another variable.
	printf("individual dig sum:%lld\n",a);
	
}

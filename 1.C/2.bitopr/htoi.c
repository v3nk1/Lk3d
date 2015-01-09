//convert given hex num to integer..

#include<stdio.h>
#define ul unsigned long

int htoi(unsigned long int tmp){

		int k=0,i=0;
		
		for(i=0; i < ((sizeof(long))*2);i++){

			ul shift = 0xf000000000000000;
			int temp = tmp & (shift>>(4*i));
			temp = temp >> (64-(4*(i+1)));
		//	printf("%d. %d\n",i,temp);
			//printf("%d. temp = %lu\n",i,temp);
			if(temp>9) return -1;
			k = 10*k+temp;
//			i++;
//			printf("%d %d\n",k,temp);
					
		}
	
	return k;

}

main(){

//while(1){
	unsigned long int i;
	printf("enter i: ");
	scanf(" %lx",&i);
//	printf("%lx\n",i);
//getchar();	
	printf("%d\n",htoi(i));
//}
}

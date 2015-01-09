#include<stdio.h>

//	\t = \b\b\b\b\b


void spaces(int l){

	int i;
	for(i=1;i<l;i++){
		printf("\t");
		}
}

main(){

	int lines;
	int _lcnt,_str,cnt;
	int scnt/* \t spaces count */;

	printf("Enter lines: ");
	scanf(" %d",&lines);
	scnt = lines;
	
	for(_lcnt=0;_lcnt<lines;_lcnt++){

		_str = 0; cnt = 0;

		for(;_str<=_lcnt;_str++){

				cnt++;
				if(cnt==1)
					spaces(scnt--);
//				else//(cnt>1)
//					printf("\t\t");
				printf("*\t");
				
			}
	
		printf("\n\n");
		}
		
}

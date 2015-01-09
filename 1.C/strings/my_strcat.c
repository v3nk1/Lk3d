#include<stdio.h>

char *my_strcat(char *dest,const char *src){
	
	static int i=0;
	int j=0;
	while(dest[i]!='\0'){
		i++;
	}
	//printf("%d\n",i);
	while(src[j]!='\0'){
		dest[i]=src[j];
		//dest[i+1]='\0';

		//printf("%c\n",dest[i]);
		//printf("%s\n",dest);
		i++;j++;

	}		

	//printf("%c\n",dest[6]);
	//printf("%d %d\n",i,j);
	//printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",dest[0],dest[1],dest[2],dest[3],dest[4],dest[5],dest[6],dest[7],dest[8],dest[9],dest[10],dest[11],dest[12],dest[13],dest[14]);
	dest[i+1]='\0';
	//return dest;

}

main(){

	char str1[50]="venkat",str2[50]="esh.Bolla";
	my_strcat(str1,str2);
	printf("%s\n",str1);

}

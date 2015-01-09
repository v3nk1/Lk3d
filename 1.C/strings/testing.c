#include<stdio.h>
char *my_strstr(const char *str1,char str2[50]){
int i=0;static int cnt=0,x=0;
while(str2[i]!='\0'){
//    printf("%d\n",i);   
      int j=0; 
   while((str1[j])!='\0'){
            printf("%d %d\n",i,j);

         if(str2[i]==str1[j]){
		x=j;
		// printf("%d %d\n",i,j);
                int k=0;
	   	for(;k<strlen(str2);k++){
              		if( str2[i+k]==str1[j+k]) {cnt++;}
             //	printf("%d\n",k);   

         	 }
	  }
	else j++;
//printf("%d %d\n",i,j);
    }
//printf("%d %d\n",i,j);
i++;
}
if(cnt==strlen(str2)) return str1+x;
 //   else printf("no such string\n");
}
main(){
char str1[50]="ven";
char *srch=my_strstr(str1,"e");      // here must assign ptr which stores the return address,that returned address is treated as base address so %s prints from that to last upto it encounters null(\0).
//printf("%s\n",my_strstr(str1,"rainy"));
}



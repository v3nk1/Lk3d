#include<stdio.h>
struct abc{
	char str[100];
}o[3]={"venkatesh","omkar","naresh"};

int srch(struct abc *o,char *s){
	int i=0;
	for(;i<sizeof o[i];i++) {//printf("%d\n",i);
		int j;   //j must declare here otherwise j is not GHAJINI; Here every time i for loop exicuted j=0 hojayegaa.
		for(j=0;j<strlen(o[i].str);j++){//printf("%d   %d\n",i,j);
			if((o[i].str[j])==*s){//char *p=&(o[i].str[j]);
				if(!strncmp(&(o[i].str[j]),s,strlen(s)))  return 1;  // c in strcmp arguments we only use pointer to char variables ie address of particular string only. thats why we are declaring *p here. and using it in strncmp.
          			}
    // else{ int z=0;return z;}// dont put else s++ here. since s++ means we are incrementing the searching element. 
			}
	}
}

main(){

//srch(o,"kat");
printf("%d\n",srch(o,"resh")); //here o itself indicates base address since o is an array.

}

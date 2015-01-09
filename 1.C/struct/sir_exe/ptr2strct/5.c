//sorting in an object.
#include<stdio.h>
struct a{
char str[100];
int len;
}o={"qwertyuiopasdfAghjklzxcvbnm",27};
void sort(struct a *o,int len){
//struct a *p=o;
  int j=0,cnt=0;
  for(;j<len;j++){//printf("j=%d\n",j);
	int i=0;
	for(;i<len-1;i++){//here in for loop len-1 is very importent
	//if((o->str[j])>(o->str[i+cnt])){char c= o->str[j]; o->str[j]=o->str[i+cnt]; o->str[i+cnt]=c;} printf("%s\n",o->str);
	if(o->str[i]>o->str[i+1]) {char temp=o->str[i]; o->str[i]=o->str[i+1]; o->str[i+1]=temp;} printf("%s\n",o->str);
	}//cnt++;
  printf("===============\n");
   }
//printf("%s\n",o->str);
}
main(){
sort(&o,o.len);
}

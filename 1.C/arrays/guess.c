//Guess outputs

#include<stdio.h>

main(){

        int a[10]={1,3,5,6};
	a[-200]=123;
	a[200]=143;

        printf("%d\n",-200[a]);
        printf("%d\n",(-200)[a]);
        printf("%d\n",a[-200]);
        printf("%d\n",*(-200+a));

}


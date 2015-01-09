#include<unistd.h>
#include<stdio.h>

main(){
int pip[2];
getchar();
pipe(pip);
getchar();

int d=dup2(pip[0],3);
getchar();
printf("pipe=%d,dup=%d\n",pip[0],d);
getchar();
}

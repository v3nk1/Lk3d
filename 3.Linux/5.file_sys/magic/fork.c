#include<stdio.h>
#include<unistd.h>

main(){

char buff[1000];
int pipefd[2];
pipe(pipefd);

int pid=fork();
if(pid==0){
//while(1){
//int rd=read(0,buff,sizeof(buff));
printf("**************************************************\n");
//write(pipefd[1],buff,rd);
//}
}
else
//while(1)
printf("==================================================\n");
}

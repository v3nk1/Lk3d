/* SEE STRACE ./A.OUT BY PRESSING ENTER KEY, SINCE U R GIVEN GETCHAR(); HERE */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

main(){
//getchar();
int pipefd[2];

printf("pipe will be created\n");
getchar(); 
pipe(pipefd);// here automatically file descriptors wil be created see "ls /proc/pid(of a.out founded by ps -Af)/fd/"			

printf("write will\n");
getchar();
char buff[1000];
write(pipefd[1],"venkatesh is very good boy",123);

printf("read will\n");
getchar();
int p=read(pipefd[0],buff,123);

getchar();
buff[p]='\0';
printf("%s\n",buff);

printf("will close read end\n");
getchar();
close(pipefd[0]);
printf("will close write end\n");
getchar();
close(pipefd[1]);

printf("end of prog\n");
getchar();
}

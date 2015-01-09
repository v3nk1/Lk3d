//write a prog, in which the parent send some data to child and child has to receive it prints the data, and the main thread will be alive until the child has complited..

//In pipes we didnt bother about synchronization, since they are designed in such a way that they will always synchronize in naturre.

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

main(){

	int fd[2];
	pipe(fd);
	char buff[100];

	switch(fork()){

		case 0://child
		//	read(fd[0],buff,sizeof(buff));
//			sleep(1);
			write(1,"Data rec frm parent: ",21);
			write(1,buff,read(fd[0],buff,sizeof(buff)));
			break;
		
		default://parent
			//sleep(10); if u give sleep here parent going to suspend for 10sec and child will block until parent write the data into the pipe..
			write(fd[1],"Welcome\n",8);
			write(1,"Data sent to child\n",19);
			break;


	}

wait(NULL);

}

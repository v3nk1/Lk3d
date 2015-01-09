//write a prog, in which the parent send some data to child and child has to receive it prints the data, and the main thread will be alive until the child has complited..

//In pipes we didnt bother about synchronization, since they are designed in such a way that they will always synchronize in naturre.

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct data{
	int i;
	char msg[12];
	};


main(){

	int fd[2];
	pipe(fd);

	switch(fork()){

		case 0://child
		//	read(fd[0],buff,sizeof(buff));
//			sleep(1);
			{struct data buf;//In a lable we can give only statements but not declarations, here case 0 is a lable and struct data buf is a declaration, u must put in braces..

			read(fd[0],&buf,sizeof(buf));
			write(1,"Data rec frm parent: ",21);//See write system call always expects that user shud pass ascii data only, even if u pass an integer then if there is an char symbol for that integer val then that char will be printed by write, suppose if u give int h=65, &h as input to write then it will print 'A' in output..

			printf("val: %d, mesg: %s\n",buf.i,buf.msg);
			break;}
		
		default://parent
			//sleep(10); if u give sleep here parent going to suspend for 10sec and child will block until parent write the data into the pipe..
			{struct data o={1234,"i'm legend"};

			write(fd[1],&o,sizeof(o));
			write(1,"Data sent to child\n",19);
			break;}


	}

wait(NULL);

}

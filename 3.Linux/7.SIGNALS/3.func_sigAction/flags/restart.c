/* This make sense only for pipe/fifo
Since in than only read operation is blocked until write operation is performed(ie.,data is ready for reading).
Actually read invokes sys_read
	sys_read inovokes here pipefs_read in primary memory of kernal space.
		so whenever u press your interuupt ^c then it comes out from kernel space and goto ur difinined handler(which is  resides in user space). Since all application defined signalHandlers are resided in userspace stack as part of current process address space only. so the blocked reading is terminated.

	In such case SA_RESTART	flag comes into picture. By using it, the process again goes back to previous state after execution of your signal handler completed.

*/

#include<stdio.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sigHandler(int signum){

	printf("registered signal%d\n",signum);

}

main(){
/*************************************  MAKING A FIFO ***************************************************/
	mkfifo("pipe",0664);

/**************************************  OPENING A FIFO *************************************************/
	int fd=open("./pipe",O_RDWR);

/**********************************  REGISTERING SIG_HANDLER TO KERNEL **********************************/
//WITH OUT THIS IF YOU PRESS ^C IT COMES OUT OF THE BLOCKED READ and  we invoked write na it prints a nothing, since the rd=0 here no read done, and terminates the process. 

	struct sigaction obj;
	obj.sa_handler= sigHandler;
	obj.sa_flags  = SA_RESTART;
	sigaction(SIGINT,&obj,NULL);
		//signal(SIGINT,sigHandler);	Automatically restarted where it previously preempted.
/******************************************* FOR RDING & WRTING **********************************************/
	char buff[20];
	int rd=read(fd,buff,sizeof(buff));
	write(1,buff,rd);

//close(fd); noneed actually.

}

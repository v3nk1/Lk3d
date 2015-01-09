#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void fileflags(int flags,char *str)
{
	printf("File flags in %s\n",str);

	printf("\tO_RDONLY flag in is: %s\n",
                       (flags & O_RDONLY) ? "on" : "off");
	printf("\tO_WRONLY flag in is: %s\n",
                       (flags & O_WRONLY) ? "on" : "off");
	printf("\tO_RDWR flag in is: %s\n",
                       (flags & O_RDWR) ? "on" : "off");
	printf("\tO_APPEND flag in is: %s\n",
                       (flags & O_APPEND) ? "on" : "off");
	
}
int main(void)
{
	int fd, flags, ret;

	char template[] = "/tmp/testXXXXXX";

	fd = mkstemp(template);
	
	flags = fcntl(fd, F_GETFL);
	fileflags(flags,"parent0");	/* Check current flags */
	
	flags = O_APPEND|O_RDONLY|O_WRONLY;	
	fcntl(fd,F_SETFL,flags);
	
	fileflags(flags,"parent1");	/* Check current flags */

	switch (fork()) {

	case 0:
		/* Child: change file status flags */

		flags = fcntl(fd, F_GETFL);	/* Fetch current flags */

		fileflags(flags,"child");	/* Check current flags */

		flags |= O_APPEND;	/* Turn O_APPEND on */
		
		break;

	default:

		/* lets test if Parent can see file changes made by child */
		wait(NULL);
		printf("Child has exited\n\n");
		
		flags = fcntl(fd, F_GETFL);
		fileflags(flags,"parent(SW)");
		break;
	}
}

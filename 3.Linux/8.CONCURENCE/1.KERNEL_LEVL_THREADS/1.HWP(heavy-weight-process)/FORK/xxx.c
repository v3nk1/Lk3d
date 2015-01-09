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


	fd = open("./test_18",O_RDONLY);
	flags = fcntl(fd, F_GETFL);
	if (flags == -1) {
		perror("fcntl - F_GETFL");
		exit(1);
	}
	fileflags(flags,"parent");	/* Check current flags */

	switch (fork()) {

	case -1:
		perror("fork");
		exit(1);

	case 0:
		/* Child: change file status flags */

		flags = fcntl(fd, F_GETFL);	/* Fetch current flags */
		if (flags == -1) {
			perror("fcntl - F_GETFL");
			exit(1);
		}
		fileflags(flags,"child");	/* Check current flags */

		flags |= O_APPEND;	/* Turn O_APPEND on */
		if (fcntl(fd, F_SETFL, flags) == -1) {
			perror("fcntl - F_SETFL");
			exit(1);
		}
		break;

	default:

		/* lets test if Parent can see file changes made by child */
		wait(NULL);
		printf("Child has exited\n\n");
		
		flags = fcntl(fd, F_GETFL);
		fileflags(flags,"parent");
		break;
	}
	exit(EXIT_SUCCESS);
}

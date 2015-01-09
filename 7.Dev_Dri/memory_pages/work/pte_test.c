#include <stdio.h>
#include <string.h>
#include <fcntl.h>

static char buf[30];

int main(void)
{
	int fd, nbr;
	int resp;

	strcpy(buf,"Test string 1 2 3 4");

	fd = open("/dev/addtrans", O_RDONLY);
	if ( fd < 0 ) {
	   printf("Error opening file /dev/addtrans\n");
	   return -1;
	}

	printf("USER: Before read: %s\n",buf);
	printf("USER: Address of buf @ %p\n",buf);

	nbr = read(fd, buf, 30);

	printf("Enter num to continue: ");
	getchar();
	printf("USER: After read: %s\n",buf);

	close(fd);
	return 0;
}

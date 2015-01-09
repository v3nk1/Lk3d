#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define UIO_DEV "/dev/uio0"


int main(int argc, char **argv)
{
	int nint;
	int ret=0;
	int uio_fd;
	uio_fd = open(UIO_DEV, O_RDWR);
	if (uio_fd < 0) {
		fprintf(stderr, "Cannot open UIO file...\n");
		return -1;
	}

	//while (1){
                read(uio_fd, &nint, sizeof(nint));
                printf("%s:Interrupts: %u\n",__func__, nint);
        //}

	return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>

#define UIO_DEV "/dev/uio0"

void * thread_func(void *arg)
{
	printf("Thread work started .....\n");
	return NULL;
}
int main(int argc, char **argv)
{
	int nint;
	int ret=0;
	int uio_fd;
	pthread_t tid;

	uio_fd = open(UIO_DEV, O_RDWR);
	if (uio_fd < 0) {
		fprintf(stderr, "Cannot open UIO file...\n");
		return -1;
	}

	while (1){
                ret = read(uio_fd, &nint, sizeof(nint));
		if(ret==sizeof(nint))
			break;
        }
	pthread_create(&tid, NULL, thread_func, NULL);
	pthread_join(tid, NULL);
	return 0;
}

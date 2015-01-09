#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
        int fd, i;
        ssize_t ret;
        char my_buf[256]={};

        fd = open( "/dev/eeprom_dev", O_RDWR );
        if(fd<0)
                printf("failed acquiring file descriptor return status %d\n",fd);

        /* write the contents of my buffer into the device */
        ret = read(fd,my_buf,sizeof(my_buf));
        if(ret<0)
                printf("read operation failed with return status %ld\n",ret);
        printf("%s\n", my_buf);
	close(fd);
}


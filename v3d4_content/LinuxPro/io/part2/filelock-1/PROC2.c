# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/file.h>
#include <stdio.h>
main(){
	int fd,loc_res;
	fd = open("./file1",O_RDWR);
	loc_res=lockf(fd,F_TLOCK,6); //lock 6 bytes
	printf(" result of locking = %d\n",loc_res);
	getchar();
}

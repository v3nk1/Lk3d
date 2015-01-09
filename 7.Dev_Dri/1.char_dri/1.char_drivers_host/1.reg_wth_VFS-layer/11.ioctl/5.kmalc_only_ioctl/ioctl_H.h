//to avoid bellow conflictions we shud use _IO family to define command numbers.. see next directory
#ifndef ioctl_H

#define ioctl_H

#include<linux/ioctl.h>

#define MAGIC 'I'
		
typedef struct rw_info{//actually no need of rw_info here
		char *buf;
		size_t size;
		int ret_val;//though this ret val of read and write has to passed to user
	}rdwr_t;

#define GET_SIZE 	_IOR(MAGIC,1,uint)
#define SET_SIZE 	_IOW(MAGIC,2,uint)
#define FLUSH_BUF	_IO(MAGIC,3)
#define FILL_CHAR 	_IOW(MAGIC,4,uint)
#define RD		_IOWR(MAGIC,5,rdwr_t *)  //user will pass a reference of the above structure
#define WR		_IOWR(MAGIC,6,rdwr_t *)  

#endif


#ifndef ioctl_H

#define ioctl_H

#include<linux/ioctl.h>
		
#define MAGICNO '*'
//#define uint unsigned //uint has pre-defined in linux/types.h

#define GET_SIZE 	_IOR(MAGICNO,1,uint) //uint *)
#define SET_SIZE 	_IOW(MAGICNO,2,uint)
#define FLUSH_BUF	_IO(MAGICNO,3)
#define FILL_CHAR 	_IOW(MAGICNO,4,uint)

#endif

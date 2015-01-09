//to avoid bellow conflictions we shud use _IO family to define command numbers.. see next directory
#ifndef ioctl_H

#define ioctl_H

#include<linux/ioctl.h>
		
#define GET_SIZE 	111//0
#define SET_SIZE 	112//1
#define FLUSH_BUF	113//2 this causing problem bcoz it conflicts with do_vfs_ioctl function in fs/ioctl.c in ksrc
#define FILL_CHAR 	114//3

#endif

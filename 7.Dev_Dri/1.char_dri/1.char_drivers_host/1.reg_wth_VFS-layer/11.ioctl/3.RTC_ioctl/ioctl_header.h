#ifndef IOCTL_H

#define IOCTL_H

#include <linux/ioctl.h>
#include "rtc_header.h"

#define MAGIC_NO 	'!'
#define Uint 		unsigned //uint has pre-defined in linux/types.h

#define RD_DAY		_IOR(MAGIC_NO,1,Uint)
#define RD_MON		_IOR(MAGIC_NO,2,Uint)
#define RD_DATE		_IOR(MAGIC_NO,3,Uint)
#define RD_YR		_IOR(MAGIC_NO,4,Uint)
#define RD_HOUR		_IOR(MAGIC_NO,5,Uint)
#define RD_MIN		_IOR(MAGIC_NO,6,Uint)
#define RD_SEC		_IOR(MAGIC_NO,7,Uint)

#define WR_DAY		_IOR(MAGIC_NO,8 ,Uint)
#define WR_MON		_IOR(MAGIC_NO,9 ,Uint)
#define WR_DATE		_IOR(MAGIC_NO,10,Uint)
#define WR_YR		_IOR(MAGIC_NO,11,Uint)
#define WR_HOUR		_IOR(MAGIC_NO,12,Uint)
#define WR_MIN		_IOR(MAGIC_NO,13,Uint)
#define WR_SEC		_IOR(MAGIC_NO,14,Uint)

#endif

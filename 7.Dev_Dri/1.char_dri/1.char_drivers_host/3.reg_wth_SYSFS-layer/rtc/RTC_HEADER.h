#ifndef __RTC__H

#define __RTC__H

#define RTC_COMD_REG 	0x70
#define RTC_DATA_REG	0x71

#define SECD 		0x00
#define MINT		0x02
#define HOUR		0x04
#define DAY		0x06
#define DATE		0x07
#define MONT		0x08
#define YEAR		0x09

#define _READ_RTC(val,cmd)	{				\
				outb(cmd,RTC_COMD_REG);		\
				val = inb(RTC_DATA_REG);	\
				}

#define _WRITE_RTC(val,cmd)      {                              \
                                outb_p(cmd,RTC_COMD_REG);       \
                                outb_p(val,RTC_DATA_REG);       \
                                }


#endif

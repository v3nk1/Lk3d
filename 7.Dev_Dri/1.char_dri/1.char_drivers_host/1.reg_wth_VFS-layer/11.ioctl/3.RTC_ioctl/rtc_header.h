
#ifndef RTC_HDR
	
#define RTC_HDR

#define RTC_CMD_REG  	0x70
#define RTC_DATA_REG 	0x71

#define SEC 	0x00
#define MIN 	0x02
#define HR	0x04
#define DAY	0x06
#define DATE	0x07
#define MON	0x08
#define YR 	0x09

#define __RD_RTC(cmd,val)	{			\
			outb(cmd,RTC_CMD_REG);		\
			val = inb(RTC_DATA_REG);	\
			}
		
			
#define __WR_RTC(cmd,val)	{			\
			outb_p(cmd,RTC_CMD_REG);	\
			outb_p(val,RTC_DATA_REG);	\
			}
			/*
			 * Here above we use outb_p to make sure that to give some delay for rtc driver,
			 * inorder to update the given value.
			 * Especially by this instruction it will exectute one NOP/dummy instruction inorder to waste
			 * 1 machine cycle.
			 */

#endif

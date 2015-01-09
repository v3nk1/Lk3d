#include<linux/io.h>
#ifndef LED_H

#define LED_H

#define GPBCON		0x56000010
#define GPBDAT		0x56000014
#define GPBUP		0x56000018

/*LED4*/
#define CON_SHIFT4	16
#define DATA_SHIFT4	8
#define UP_SHIFT4	8

#define CON_IN4	 	0x00<<CON_SHIFT4 
#define CON_OUT4	0x01<<CON_SHIFT4
#define CON_DREQ4	0x10<<CON_SHIFT4
#define CON_RES4	0x11<<CON_SHIFT4

#define LED4_ON		0<<DATA_SHIFT4
#define LED4_OFF	1<<DATA_SHIFT4

#define PULUP_EN4	0<<UP_SHIFT4
#define PULUP_DIS4	1<<UP_SHIFT4

/*LED3*/
#define CON_SHIFT3	14
#define DATA_SHIFT3	7
#define UP_SHIFT3	7

#define CON_OUT3	0x01<<CON_SHIFT3

#define LED3_ON		0<<DATA_SHIFT3
#define LED3_OFF	1<<DATA_SHIFT3

#define PULUP_EN3	0<<UP_SHIFT3
#define PULUP_DIS3	1<<UP_SHIFT3

#define L4ON_L3OFF	LED4_ON|LED3_OFF
#define L4OFF_L3ON	LED4_OFF|LED3_ON

#define WRITE_REG(val,addr)		{				\
					iowrite32(val,addr);		\
					}


#endif

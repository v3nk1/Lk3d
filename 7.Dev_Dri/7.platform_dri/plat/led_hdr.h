#include<linux/io.h>
#ifndef LED_H

#define LED_H

#define GPBCON		0x56000010
#define GPBDAT		0x56000014
#define GPBUP		0x56000018

#define CON_SHIFT	16
#define DATA_SHIFT	8
#define UP_SHIFT	8

#define CON_IN	 	(0x00<<CON_SHIFT) 
#define CON_OUT		(0x01<<CON_SHIFT)
#define CON_DREQ	(0x10<<CON_SHIFT)
#define CON_RES		(0x11<<CON_SHIFT)

#define LED_ON		(0<<DATA_SHIFT)
#define LED_OFF		(1<<DATA_SHIFT)

#define PULUP_EN	(0<<UP_SHIFT)
#define PULUP_DIS	(1<<UP_SHIFT)

#define WRITE_REG(val,addr)	iowrite32(val,addr);

#endif

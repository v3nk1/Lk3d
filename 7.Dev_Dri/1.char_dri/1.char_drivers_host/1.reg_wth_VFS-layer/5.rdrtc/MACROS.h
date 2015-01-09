
#ifndef MACROS

#define MACROS

#define __RD_SEC(tmp) {\
		outb(0x00,0x70);\
		tmp = inb(0x71);\
		}

#define __RD_MIN(tmp) {\
		outb(0x02,0x70);\
		tmp = inb(0x71);\
		}

#define __RD_HOUR(tmp) {\
		outb(0x04,0x70);\
		tmp = inb(0x71);\
		}

#define __RD_DAY(tmp) {\
		outb(0x06,0x70);\
		tmp = inb(0x71);\
		}

#define __RD_DATE(tmp) {\
                outb(0x07,0x70);\
                tmp = inb(0x71);\
                }

#define __RD_MON(tmp) {\
                outb(0x08,0x70);\
                tmp = inb(0x71);\
                }

#define __RD_YEAR(tmp) {\
                outb(0x09,0x70);\
                tmp = inb(0x71);\
                }



/*
__WR_HOUR
__WR_MIN
__WR_SEC

__WR_DATE
__WR_MON
__WR_YR
*/
#endif

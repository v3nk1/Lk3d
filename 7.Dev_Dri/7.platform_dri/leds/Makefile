obj-m := led_plat.o
obj-m += led_plat1.o
obj-m += led_plat2.o
obj-m += led_plat3.o

#ARCH:=arm
#CROSS_COMPILE:=arm-linux-

KDIR :=/embedded/mini2440/uImages/eeprom/linux-3.15.3

PWD := $(shell pwd)

default:
	 $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	arm-linux-gcc test.c -o test	 
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean













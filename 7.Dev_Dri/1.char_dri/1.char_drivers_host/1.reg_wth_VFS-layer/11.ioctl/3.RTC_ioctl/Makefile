obj-m:=	rtc_driver.o

KDIR=/lib/modules/$(shell uname -r)/build

all:	rtc_driver.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	insmod rtc_driver.ko #to automate the job of inserting module


clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rmmod rtc_driver #to automate the job of removing the module

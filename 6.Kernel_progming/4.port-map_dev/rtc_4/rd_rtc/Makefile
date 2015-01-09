obj-m:=rd_rtc.o

O:=

KDIR=/lib/modules/$(shell uname -r)/build 

all:	rd_rtc.c 
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	insmod rd_rtc.ko

clean:
		
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rmmod rd_rtc

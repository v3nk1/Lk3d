obj-m  := usbprobe.o
obj-m  += usbdrv.o
obj-m  += usbdrv2.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD)  modules
clean: 
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean 
	


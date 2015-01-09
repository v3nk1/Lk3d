obj-m:=chrdrv_udev.o

KDIR=/lib/modules/$(shell uname -r)/build

all:	chrdrv_udev.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	insmod chrdrv_udev.ko #to automate the job of inserting module


clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rmmod chrdrv_udev #to automate the job of removing the module

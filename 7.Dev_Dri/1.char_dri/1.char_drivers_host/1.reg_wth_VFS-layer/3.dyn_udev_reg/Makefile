obj-m:=chrdrv_udev.o
obj-m+=chrdrv_udev1.o

KDIR=/lib/modules/$(shell uname -r)/build

all:chrdrv_udev.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules


clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

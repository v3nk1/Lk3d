obj-m:=	misc.o

KDIR=/lib/modules/$(shell uname -r)/build

all:	misc.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	insmod misc.ko #to automate the job of inserting module


clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rmmod misc #to automate the job of removing the module

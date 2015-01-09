
obj-m:=	reg_chrdev.o

KDIR=/lib/modules/$(shell uname -r)/build

all:	reg_chrdev.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	insmod reg_chrdev.ko 

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rmmod reg_chrdev 

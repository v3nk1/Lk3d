obj-m:=apic.o

KDIR=/lib/modules/$(shell uname -r)/build 

all:	apic.c 
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules


clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

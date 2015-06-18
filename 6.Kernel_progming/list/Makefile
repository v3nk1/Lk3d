obj-m+= main.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	dmesg -C	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

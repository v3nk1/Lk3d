obj-m := ins.o

KDIR:=/lib/modules/$(shell uname -r)/build

all:	ins.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

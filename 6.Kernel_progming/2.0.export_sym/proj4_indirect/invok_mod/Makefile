obj-m := invok.o

KDIR:=/lib/modules/$(shell uname -r)/build

all:	invok.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

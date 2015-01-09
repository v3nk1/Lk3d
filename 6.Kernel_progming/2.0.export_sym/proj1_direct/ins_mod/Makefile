obj-m:= ins.o

KDIR:=/lib/modules/$(shell uname -r)/build

ins.o:	ins.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

modules_install:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

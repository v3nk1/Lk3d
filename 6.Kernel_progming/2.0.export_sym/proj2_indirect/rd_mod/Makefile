obj-m:=rd.o

KDIR=/lib/modules/$(shell uname -r)/build

all:	rd.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

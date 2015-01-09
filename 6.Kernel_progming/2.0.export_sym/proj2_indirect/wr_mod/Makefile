obj-m:=wr.o

KDIR=/lib/modules/$(shell uname -r)/build

all:	wr.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

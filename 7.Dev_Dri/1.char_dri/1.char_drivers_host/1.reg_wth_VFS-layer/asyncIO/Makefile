obj-m:=chrdrv_udev.o

KDIR=/lib/modules/$(shell uname -r)/build

all:chrdrv_udev.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	@gcc reader.c -o reader
	@gcc writer.c -o writer

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	@rm -rf reader writer a.out *~ *.swp

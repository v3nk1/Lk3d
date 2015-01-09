obj-m:=ptdump.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	@dmesg -C
	@insmod ptdump.ko
	@gcc pte_test.c
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rmmod ptdump

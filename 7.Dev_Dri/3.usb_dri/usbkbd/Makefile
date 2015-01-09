obj-m :=usbkbd1.o
obj-m +=usbkbd2.o
obj-m +=usbkbd3.o
#obj-m +=usbkbd4.o
#obj-m +=usbkbd.dev.o
#obj-m +=usbmouse.o

KDIR=/embedded/mini2440/uImages/eeprom/linux-3.15.3
#KDIR=/lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	arm-linux-gcc test_usbkbd.c -o test_usbkbd
	dmesg -C

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

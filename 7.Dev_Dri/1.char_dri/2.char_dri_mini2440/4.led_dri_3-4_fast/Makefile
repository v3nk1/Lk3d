obj-m:=	reg_chrdev.o


####################################################################################################################
#	Here the path of KDIR must be the target kernel headers path <ie., version shud match with target uImage>  #
#	Since uImage has created by a kernel source na, So kdir linux kernel stamp shud match with that.	   #
####################################################################################################################

KDIR=/home/ven/venky/4.Embd_C/mini2440/rootfs/minifs/lib/modules/3.12.0/build

ARCH:=arm
CROSS_COMPILE=arm-linux-

all:	reg_chrdev.c
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

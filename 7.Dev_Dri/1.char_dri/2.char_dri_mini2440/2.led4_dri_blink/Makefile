obj-m:=	reg_chrdev.o


####################################################################################################################
#	Here the path of KDIR must be the target kernel headers path <ie., version shud match with target uImage>  #
#	Since uImage has created by a kernel source na, So kdir linux kernel stamp shud match with that.	   #
####################################################################################################################

KDIR=/embedded/mini2440/uImages/eeprom/linux-3.15.3

#ARCH:=arm
#CROSS_COMPILE=arm-linux-

all:	reg_chrdev.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

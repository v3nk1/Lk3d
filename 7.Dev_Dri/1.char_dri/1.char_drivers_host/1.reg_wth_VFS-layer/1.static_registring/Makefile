obj-m:=chrdrv_stat.o

NOD_PATH:=/dev
NOD_NAME:=my_chr_dev

MAJOR:=300
MINOR:=0

EXIST:=

KDIR=/lib/modules/$(shell uname -r)/build

all:	mknod
	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

	@# OR use M instead of SUBDIRS		\
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

mknod:	
	@#to create a node with given major,minor no in a given path
	@if [ -e $(NOD_PATH)/$(NOD_NAME) ]; \
	then echo "Already created" && EXIST=1 ; \
	else  EXIST=0 && mknod $(NOD_PATH)/$(NOD_NAME) c $(MAJOR) $(MINOR); \
	fi;

clean:
	@#to remove the created node..
	@rm -rf $(NOD_PATH)/$(NOD_NAME)
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

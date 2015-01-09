obj-m:=mutex.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	${MAKE} -C ${KDIR} SUBDIRS=${PWD} modules
	insmod mutex.ko
clean:
	${MAKE} -C ${KDIR} SUBDIRS=${PWD} clean
	rmmod mutex

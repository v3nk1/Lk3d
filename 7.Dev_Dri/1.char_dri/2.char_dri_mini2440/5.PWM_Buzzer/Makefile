obj-m:=buzzer2.o

KDIR=/embedded/mini2440/uImages/eeprom/linux-3.15.3/
all:
	${MAKE} -C ${KDIR} M=${PWD} modules
clean:
	${MAKE} -C ${KDIR} M=${PWD} clean

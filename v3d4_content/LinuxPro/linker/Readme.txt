32-bit o/p on 64-bit:
====================

# gcc -m32 -c main.c 
# ld -melf_i386 -o main -dynamic-linker /lib/ld-linux.so.2 /usr/lib32/crt1.o /usr/lib32/crti.o main.o -lc /usr/lib32/crtn.o -Tlscript.ld

64-bit:
=======
# gcc -c main.c

# ld -o main -dynamic-linker /lib/x86_64-linux-gnu/ld-2.19.so /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o main.o -lc /usr/lib/x86_64-linux-gnu/crtn.o -Tlscript.ld 


Verify Output:
=============

	# objdump -x <executable-name>
	# readelf -a <executable-name>
	# nm -n <executable-name>

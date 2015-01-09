// store two 2bytes data in a 4 byte container.

#include<stdio.h>
#define STR(a,b,c) c=b|(unsigned int)a<<16; // here becoz of type cast you get d output if u remove d type cast then a<<16 becomes zero. w/o type cast u want to achive 
			
#define PRNT_HEX(c) printf("%x\n",c);
main(){
unsigned short int a=0xaabb,b=0xccdd;
unsigned int c;
STR(a,b,c)
PRNT_HEX(c)
}

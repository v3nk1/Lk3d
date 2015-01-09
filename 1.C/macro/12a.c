#include<stdio.h>

#define IS_REG(a) if(a&1) printf("true\n"); else printf("false\n");
#define IS_CHAR(a) if(a&1<<1) printf("true\n"); else printf("false\n");
#define IS_BLOCK(a) if(a&1<<2) printf("true\n"); else printf("false\n");
#define IS_LINK(a) if(a&1<<3) printf("true\n"); else printf("false\n");
#define IS_DIR(a) if(a&1<<4) printf("true\n"); else printf("false\n");
#define IS_FIFO(a) if(a&1<<5) printf("true\n"); else printf("false\n");
#define IS_SOCKET(a) if(a&1<<6) printf("true\n"); else printf("false\n");

#define MACRO(data,x) x(data)

main(){

	unsigned char a=255;

	MACRO(a,IS_REG)
	MACRO(a,IS_CHAR)
	MACRO(a,IS_BLOCK)
	MACRO(a,IS_LINK)
	MACRO(a,IS_DIR)
	MACRO(a,IS_FIFO)
	MACRO(a,IS_SOCKET)
	MACRO(a,IS_REG)

}

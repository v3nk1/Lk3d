#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

#define MB      123
#define KB      321
#define B       213

char arr[]={'-','\\','|','/'};
	
char data_buf[150000];/*150KB*/

typedef struct fileinfo{

	char name[100];
	int szB;

	}flinfo_t;

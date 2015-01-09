#include<linux/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

#define NOTFOUND        "notfound\0"
#define FOUND           "found\0"
#define RDCOMPLETE      "EOF\0"
		  /**
 		   * We have to send including '\0' since we are using strcmp() on client side to know the status
         	   */

#define SIZE_RDCOMP     4 /* Including '\0' */
#define SIZE_NTFND      9 /* Including '\0' */
#define SIZE_FND        6 /* Including '\0' */

#define MB      123
#define KB      321
#define B       213

char arr[]={'-','\\','|','/'};
	
typedef struct PACKET{
        int eof;
        char data_buf[150000];/*150KB*/
        size_t data_sz;/*Only data size*/

        }pack_t;

typedef struct fileinfo{

	char name[100];
	int szB;

	}flinfo_t;

#include <malloc.h>

#define SND	"&%^#"
#define RCV	"$&_@"
#define REG	"!(*)"
#define DREG	"#(D)"
#define SRVCHK	"}7&)"
#define NOK	"|VV|"
#define OK	">0K<"
#define ILGCLI	"!!_G"

#define CONNCHK		{								\
			if(!rd){							\
				printf("%s: Client Disconected\n",cmname);		\
				raise(SIGKILL);						\
				}							\
			else if(rd<0){ 							\
				perror("recv");						\
				continue;						\
				}							\
			}	

char cmd[5];

typedef struct {
	size_t sndr_sz;
	size_t sub_sz;
	size_t msg_sz;
	}attr_t;

typedef struct {
/*	char *sndr;
	char *subjct;
	char *msg;
*/	char sndr[20];
	char subjct[81];
	char msg[513];
	attr_t attr;
	}sercli_t;


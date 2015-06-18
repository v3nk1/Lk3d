#include <string.h>
#define DATA "/mydata"

struct mydata {
	sem_t sem;
	int a;
	int b;
};

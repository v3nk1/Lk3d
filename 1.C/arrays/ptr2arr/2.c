#include <stdio.h>

main(){

	int (*a)[5];

	printf("%d %d\n",sizeof(a),sizeof(*a));
}

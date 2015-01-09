#include<stdio.h>

main(){

	int k=10;
        const int *kp;
	kp = &k;

//\
	*kp++ : *kp then kp++	\
	(*kp)++: (*kp)=(*kp)+1;	\
		
	printf("%d\n",*kp++);  //after this operations kp not at all pointing to a valid address, points to garbage/junk
	//printf("%d\n",++(*kp));

}

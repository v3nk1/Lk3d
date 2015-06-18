#include<stdio.h>

main(){

	float f=4.725123457;
	double	d=4.1234567;
	long double ld=4.89;	
//	printf("%f===\n",f);
//	printf("%f %lf %Lf\n",f,d,ld);
	
	f=41.1;
	printf("%e %g\n",f,f);
		//4.110000+01, 41.1(eleminate 0's)
/*	if(f==4.5)
		printf("i'm in if\n");

	else 
		printf("i'm in else\n");
*/

/*	printf("%d\n",f==4.725);
	printf("%d\n",d==4.725);
	printf("%d\n",f==d);
*/
}

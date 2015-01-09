#include<stdio.h>
main()
{
int a=-5;
unsigned int b=1;      
if(a>b){                   // never compare signed to unsigned, if u cmpare the compile done the type cast by conv signed to unsigned..so the (-ve) value got as large value since it includes sign bit as data bit.
printf("a is big");
}
else{
printf("b is big");
}
}

//&a and a miths and facts

#include<stdio.h>
main(){
int a[2]={........};
a	//symbol name indicates itself 0th element address/base address
&a	//it also indicates 0th element address,but d diffnce is, if u pass it in a function it passes entire array address. then           u increment it wil increment by total array size. But the catching argument in the formal argument must be a pointer to array of 2 integers type ie.. INT (*PA)[2]; BRACKET FOR PTR IS BCOZ SUB SCRIPT HAS HEIGHEST PREOIRITY. SO IT MUST BE FORMAL ARGUMENT WHEN YOU PASS &a AS AN ACTUAL ARGUMENT.
a+1	//increments by 4 bytes(type size) only
&a+1	//increments by entire array size.ie., 8 bytes(type size*no_elements)

int b[2][3]={............};
b	//symbol name indicates 0th row 0th column element address.(but of column size) 
&b	//its also same,but to access we use pointer to array ie., INT (*PB)[2][3];
b+1	//increments by (3*4) ie.,COLOUMN SIZE*data type size. ( see without 1st subscript)
&b+1	//increments by entire array size.ie., 2*3*4=24 bytes.


int c[2][3][4]={1,2,3,4,5,6,0,0,6,7};int i,j;
c	//it indicates c[0][0][0] element address.
&c	//it also indicates 0th elemnt but entire array address. ptr to array.. INT (*PC)[2][3][4];
c+1	//increments by (3*4*type size)=48 bytes  ( see without 1st subscript)
&c+1	//increments by entire array size ie., 2*3*4*type size=96 bytes

//for(i=0;i<2;i++){
//	for(j=0;j<2;j++)
	printf("%p %p %p\n",a,a+1,&a+1);
//printf("%p\n",a);
}

//Little endian to big endian

#include<stdio.h>

unsigned int little2big(int x){

	int res=0;
	char *ptr=(char *)&res;

	int i;
	for(i=0;i<4;i++)
		ptr[i]=*((char *)&x+(3-i));
	
	return res;

}

main(int argc,char *argv[]){

	if(argc != 3){
		printf("Usage: <%s> <input_format> <output_format>\n",argv[0]);
		printf("Formates: -d/-o/-x\n");
		return;
		}

	int no;
	char ch;
	if(*argv[1]=='-')
		ch=*(argv[1]+1);
	else
		ch=*argv[1];
	switch(ch){
		
		case 'x':
			printf("Enter hexa value to convert: ");
			scanf(" %x",&no);
			break;
		case 'o':
			printf("Enter octal to convert: ");
			scanf(" %o",&no);
			break;
		case 'd':
			printf("Enter decimal to convert: ");
			scanf(" %d",&no);
			break;
		default:
			printf("Enter valid input option flag\n");
			return;
			}

	if(*argv[2]=='-')
		ch=*(argv[2]+1);
	else
		ch=*argv[2];
	switch(ch){
		
		case 'x':
			printf("result: %#x\n",little2big(no));
			break;
		case 'o':
			printf("result: %#o\n",little2big(no));
			break;
		case 'd':
			printf("result: %u\n",little2big(no));
			break;
		default:
			printf("Enter valid output option flag\n");
			return;
			}

}

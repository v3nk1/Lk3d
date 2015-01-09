#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stu{
	char name[25];
	char gen;
	int rolno;
	float hei;
	char grade;
};

main(){


	int i,n;
	printf("enter how many students:\n");scanf("%d",&n);
	struct stu o[n];
	
	FILE *stream;


//rewind(stream);  rewind is needed in gets() ,  puts() functions only.not required in binary reading. ftell also.
																

	struct stu buff[n];
	stream=fopen("srch.file","r+");if(!stream) perror("fopen"),exit(2);
	fread(buff,sizeof(buff),1,stream);
	//fclose(stream);

		//printf("----------------------------------------------------------\n");
		printf("\t\t\t\t==========================================================\n");
		printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
		printf("\t\t\t\t==========================================================\n");
	for(i=0;i<sizeof(buff)/sizeof(struct stu);i++){
		printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);



		if(i<sizeof(buff)/sizeof(struct stu)-1)	printf("\t\t\t\t----------------------------------------------------------\n");
	}	

	//printf("----------------------------------------------------------\n");
	printf("\t\t\t\t==========================================================\n");   

char rfrnce;
int p;
	srch_menu();
	printf("\nenter ref code:");
	scanf(" %c",&rfrnce);

}

//program to understand how read/write functions works on a file. by writing array of structure objects to a file in binary formate and reading it from file by formated i/o functions i.e., printf.

#include<stdio.h>
#include<stdlib.h>
struct stu{
	char name[25];
	char gen;
	int rolno;
	float hei;
	char grade;
};
main(){

/* DECLARING HOW MANY STUDENTS FOR DATA WR/RD ING */

	int i,n;
	printf("enter how many students:\n");scanf("%d",&n);
	struct stu o[n];
	
	FILE *stream;

/* FOR READING DATA IF NO DATA IN THE FILE/ REPLACE BY NEW DATA */

		for(i=0;i<sizeof(o)/sizeof(struct stu);i++){
			printf("enter name,gen,rolno,hei,grade of stu%d\n",i+1);
			scanf(" %s %c %d %f %c",o[i].name,&o[i].gen,&o[i].rolno,&o[i].hei,&o[i].grade);
		}

/* OPEN/CREATE A FILE IN WRITING MODE */

	stream=fopen("srch.file","w");if(!stream) perror("fopen"),exit(1);

/* WRITING THE ENTERED DATA INTO FILE AND CLOSEING THE FILE */

	fwrite(o,sizeof(o),1,stream);
	fclose(stream);
//rewind(stream);  rewind is needed in gets() ,  puts() functions only.not required in binary reading. ftell also.
																

/* DATA READING FROM THE FILE AND STORING IN A TEMPARORY STRUCTURE TYPE BUFFER */

	struct stu buff[n];
	stream=fopen("srch.file","r");if(!stream) perror("fopen"),exit(2);
	fread(buff,sizeof(buff),1,stream);
	fclose(stream);

/* PRINTING READED BINARY DATA BY FORMATED I/O FUNCTIONS */

		//printf("----------------------------------------------------------\n");
		printf("\t\t\t\t==========================================================\n");
		printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
		printf("\t\t\t\t==========================================================\n");
	for(i=0;i<sizeof(buff)/sizeof(struct stu);i++){
		printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);


/* CONDITION FOR LEAVING LAST ENTITY UNDERLINE */

		if(i<sizeof(buff)/sizeof(struct stu)-1)	printf("\t\t\t\t----------------------------------------------------------\n");
	}	

	//printf("----------------------------------------------------------\n");
	printf("\t\t\t\t==========================================================\n");

}

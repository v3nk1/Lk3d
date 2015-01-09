#include<stdio.h>
#include<stdlib.h>
struct stu *ptr,*buff;
//#include"search.c"
//int *buff,*ptr;
struct stu{
	char name[25];
	char gen;
	int rolno;
	float hei;
	char grade;
};
main(){

	ptr=(struct stu *)malloc(1*sizeof(struct stu));
	int i,n;
	printf("\nenter how many students:");scanf("%d",&n);
	ptr=(struct stu *)realloc(ptr,n*sizeof(struct stu)-1);
//	struct stu o[n];
	
	FILE *stream;


/*		for(i=0;i<sizeof(o)/sizeof(struct stu);i++){
			printf("enter name,gen,rolno,hei,grade of stu%d\n",i+1);
			scanf(" %s %c %d %f %c",o[i].name,&o[i].gen,&o[i].rolno,&o[i].hei,&o[i].grade);
		}


	stream=fopen("srch.file","w");if(!stream) perror("fopen"),exit(1);


	fwrite(o,sizeof(o),1,stream);
	fclose(stream);
//rewind(stream);  rewind is needed in gets() ,  puts() functions only.not required in binary reading. ftell also.
																
*/

	buff=(struct stu *)malloc(1*sizeof(struct stu));
	buff=(struct stu *)realloc(ptr,n*sizeof(struct stu)-1);

//	struct stu buff[n];
	stream=fopen("srch.file","r");if(!stream) perror("fopen"),exit(2);
	fread(buff,sizeof(buff),1,stream);
	fclose(stream);
/*		//printf("----------------------------------------------------------\n");
		printf("\t\t\t\t==========================================================\n");
		printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
		printf("\t\t\t\t==========================================================\n");
	for(i=0;i<sizeof(buff)/sizeof(struct stu);i++){
		printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);



		if(i<sizeof(buff)/sizeof(struct stu)-1)	printf("\t\t\t\t----------------------------------------------------------\n");
	}	

	//printf("----------------------------------------------------------\n");
	printf("\t\t\t\t==========================================================\n");   */

char ref;
	srch_menu();
	printf("\nenter ref code:");
	scanf(" %c",&ref);

	search(ref,n);
}

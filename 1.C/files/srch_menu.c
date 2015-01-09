#include<stdio.h>

void srch_menu(){
printf("\t\t\t\t\t\t  MENU\n");
printf("\t\t\t\t\t===========================\n");
printf("\t\t\t\t\t| code\t|\tsearch by |\n");
printf("\t\t\t\t\t===========================\n");
printf("\t\t\t\t\t| n/N\t|\t  name    |\n");
printf("\t\t\t\t\t| h/H\t|\t  height  |\n");
printf("\t\t\t\t\t| g/G\t|\t  gender  |\n");
printf("\t\t\t\t\t| r/R\t|\t  rollno  |\n");
printf("\t\t\t\t\t| q/Q\t|\t  grade   |\n");
printf("\t\t\t\t\t| u/U\t|\t  update  |\n");
printf("\t\t\t\t\t===========================\n");

}

manipulate_rec(){

if(rfrnce=='u'||rfrnce=='U'){
	char name[25];int rolnum;
	printf("enter name, rollnum:");
	scanf("%s%d",name,&rolnum);
	if(!strcmp(buff[i].name,name) && (buff[i].rolnum==rolnum)) fwrite()

}

//int i;
if(rfrnce=='n'||rfrnce=='N'){
			char name[25];
			printf("enter name:");
			scanf("%s",name);
		for(i=0;i<n;i++){

			if(!strcmp(buff[i].name,name)){
				printf("\t\t\t\t==========================================================\n");
                		printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
                		printf("\t\t\t\t==========================================================\n");

				printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);
			}
		
}}
if(rfrnce=='h'||rfrnce=='H'){
                        float hei;
                        printf("enter hei:");
                        scanf("%f",&hei);
                for(i=0;i<n;i++){

                        if(buff[i].hei==hei)
					{ 
				p++;
				if(p==1){
                                printf("\t\t\t\t==========================================================\n");
                                printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
                                printf("\t\t\t\t==========================================================\n");
				}
                                printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);
                        }
                
}}

if(rfrnce=='g'||rfrnce=='G'){
                        char gen;
                        printf("enter gender(m/f):");
                        scanf(" %c",&gen);p=0;
                for(i=0;i<n;i++){

                        if((buff[i].gen==gen)){
				p++;
				if(p==1){
                                printf("\t\t\t\t==========================================================\n");
                                printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
                                printf("\t\t\t\t==========================================================\n");
				}
                                printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);
                        }
               
}}

if(rfrnce=='r'||rfrnce=='R'){
                        int  rolno;
                        printf("enter rollno:");
                        scanf("%d",&rolno);p=0;
                for(i=0;i<n;i++){

                        if(buff[i].rolno==rolno)
				{
				p++;
				if(p==1){
                                printf("\t\t\t\t==========================================================\n");
                                printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
                                printf("\t\t\t\t==========================================================\n");
				}
                                printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);
                        }
               
}}

if(rfrnce=='q'||rfrnce=='Q'){
                        char gra;
                        printf("enter grade:");
                        scanf(" %c",&gra);p=0;
                for(i=0;i<n;i++){

                        if((buff[i].grade==gra)){
				p++;
				if(p==1){
                                printf("\t\t\t\t==========================================================\n");
                                printf("\t\t\t\t|s.no|\t name\t\t gen\t rollno\t height\t grade   |\n");
                                printf("\t\t\t\t==========================================================\n");
				}
                                printf("\t\t\t\t| %d  |\t %-15s  %c\t  %d\t  %.1f\t   %c     | \n",i+1,buff[i].name,buff[i].gen,buff[i].rolno,buff[i].hei,buff[i].grade);
                        }
                }



}
}

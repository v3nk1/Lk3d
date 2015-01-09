#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

#define lSIZE	1024	/*line hold buffer size*/
#define hSIZE	1024	/*header hold buff size*/

int Getline(int fd,char *line){/*It will return a line in a given fd */

	int i;/*to hold line charecters cnt*/
	int rd;
	char ch;

        i=0;  /*To make new line starting from zero ie., line[0] */

	if(fd<3) return 0;

        /*To remove junk values and fill line array with 0's*/
	//bzero(line,sizeof(line)); Here sizeof line returns only 4, since in this block line is char * so 4bytes
	memset(line,'\0',lSIZE);

        while(1){/*This while is for characters iterations in a line */
                        
		rd = read(fd,&ch,1);
                if(!rd || ch=='\n')
                        	break;
                else{
                	line[i++]=ch;
//                      printf("%c",ch);
                     }
           }
//	printf("ret rd: %d\n",rd);
        return rd;/*EOF reached then it will return EOF ie., 0*/

}

int Gethdr(char *line,char *hdr){

	int i=0;
	int hpos;	/*hash position*/
	int ipos;
	int quotpos1=-1,quotpos2=-1;

	bzero(hdr,hSIZE);
	for(;i<1024;i++){
		if(line[i]=='#')
				hpos=i;
		if(line[i]=='i')
				ipos=i;
		if(line[i]=='"')
				quotpos1=i;
		}
	i=hpos+1;	/* now i is pointing to next char of # */
	for(;i<lSIZE-hpos+1;i++){
		if(line[i]==' ' || line[i]=='\t');

		else if(line[i]=='i'){
				ipos= i;
				break;
				}
		else
			return -1;
		}
	if(!strncmp(line+i,"include",7)){
//		printf("%s\n",line);
		i=ipos+6+1;	/* now i is pointing to next char of " */
		for(;i<lSIZE-ipos+1;i++){
//			printf("$%c\n",line[i]);
			if(line[i]==' ' || line[i]=='\t');
			else if(line[i]=='"'){
					quotpos1= i;
					break;
					}
                	else
                        	return -1;
                	}
		}
	else 
		return -1;
	
	i=quotpos1+1;
	for(;i<lSIZE-quotpos1+1;i++){

                        if(line[i]=='"'){
//				printf("$%c\n",line[i]);
                                        quotpos2= i;
                                        break;
                                        }

                        }

	if(quotpos2<0)
			return -1;

	int j=0;
	for(i=quotpos1+1;i<quotpos2;i++){
				hdr[j++]=line[i];
			}
//		hdr[j]='\0';		its no need since we flush hdr with 0 at start of this function
//	printf("%s\n",hdr);

}

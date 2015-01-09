#define LINE_EMPTYING	{				\
                        printf("jajaja\n");		\
                        int j=i;			\
                        while(1){			\
                                if(j==lSIZE) break;	\
                                line[j++]=' ';		\
                                }			\
                      	}




int line_comment(char *line){	//

	char buff[3];
	int i=0;
	unsigned int offset;

	//printf("line: %s\n",line);
	while(1){
		if(i==lSIZE) break;
	//	strncpy(buff,line+i,sizeof(buff));
		buff[0]=line[i];buff[1]=line[i+1];buff[2]='\0';
		//printf("%s\n",buff);
		if(!strcmp(buff,"//"))	{
				LINE_EMPTYING;
				offset = i;
				}
		i++;
		}

	return offset;
}

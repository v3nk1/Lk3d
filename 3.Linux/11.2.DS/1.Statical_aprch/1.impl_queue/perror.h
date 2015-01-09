//this is my own error msg displayer, works like as perror;

#define SUCC 0

#define FAIL (-1)
#define EFULL -2
#define EEPTY -3
#define EPOL -4
#define EMAX -5

int errno;

void my_errmsg(char *fun_name){

	switch(errno){
	
		case FAIL : 	printf("%s : Failed\n",fun_name);
				break;
		case EFULL: 	printf("%s : Que has fulled\n",fun_name);
				break;
		case EEPTY: 	printf("%s : Que is empty\n",fun_name);
				break;
		case EPOL : 	printf("%s : Unrecognized policy\n",fun_name);
				break;
		case EMAX : 	printf("%s : Invalid max value Out of range\n",fun_name);
				break;
		case SUCC : 	printf("%s : Success\n",fun_name);
				break;
	}

}		

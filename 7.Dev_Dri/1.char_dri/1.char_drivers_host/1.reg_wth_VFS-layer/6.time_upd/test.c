#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

#include"main_menu.c"

void update(int cnt){
	int i;
	for(i=0;i<cnt;i++) printf("\b");
	
}

main(){

	char cho;

	int fd = open("/dev/caldev123",O_RDWR);
		if(fd<0) perror("open"),exit(123);

	char tot[100];

while(1){
	
	menu();
	printf("Enter ur choice: ");
	scanf(" %c",&cho);

	switch(cho){
		
	/*		case 'D':	
				write(fd,"Dt",1);
				printf("%d\n",read(fd,tot,sizeof(tot)));
				printf("date: %s\n",tot);
				break;
			case 'M':
				write(fd,"M",1);
				read(fd,tot,sizeof(tot));
				printf("month: %s\n",tot);
				break;
			case 'Y':
				write(fd,"Y",1);
				read(fd,tot,sizeof(tot));
				printf("year: %s\n",tot);
				break;
			case 'h':
				write(fd,"h",1);
				read(fd,tot,sizeof(tot));
				printf("hour: %s\n",tot);
				break;
			case 'm':
				write(fd,"m",1);
				read(fd,tot,sizeof(tot));
				printf("min: %s\n",tot);
				break;
			case 's':
				write(fd,"s",1);
				read(fd,tot,sizeof(tot));
				printf("sec: %s\n",tot);
				break;
	*/		case 't':
				while(1){
                                write(fd,"t",1);
                                read(fd,tot,sizeof(tot));
                                printf("time: %s",tot);
				update(17);
				}
                                break;

			case 'd':
                                write(fd,"d",1);
                                read(fd,tot,sizeof(tot));
                                printf("date: %s\n",tot);
                                break;

			case 'T':
				while(1){
				write(fd,"T",1);
				read(fd,&tot,sizeof(tot));
				printf("calender: %s",tot);
				update(38);
				}
				break;

			case 'x':case 'X':case 'q':
						return;
			default:
				printf("Invalid choice\n");
				break;

	}


}

close(fd);
}

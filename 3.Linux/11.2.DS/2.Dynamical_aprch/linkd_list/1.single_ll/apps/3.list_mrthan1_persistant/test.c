#include<stdio.h>
//extern void backup(void);
//#include"./backup/blink.c" we already linked in make file while compiling

main(){

	char ch;

	printf("\nBackup loading ");
	fflush(stdout);
	blink_dot();
	
	load_backup();

	while(1){

		menu();
		printf("enter your choice(CODE):");
		scanf(" %c",&ch);
		if(ch == '0' || ch == 'x' || ch == 'X'){ /*come out of main loop*/
                                    char ext;
                                    printf("Are sure exit to main menu [y/n]: ");
                                    scanf(" %c",&ext);
                                    if(ext == 'y' || ext == 'Y'){
							        printf("\nBackup saving ");
							        fflush(stdout);
							        blink_dot();
							        save_backup();
                                                                return;
								}

                                    if(ext == 'n' || ext == 'N')
                                                               continue;
                                    else
                                         continue;
			}

		menuHandler(ch);

	}

}

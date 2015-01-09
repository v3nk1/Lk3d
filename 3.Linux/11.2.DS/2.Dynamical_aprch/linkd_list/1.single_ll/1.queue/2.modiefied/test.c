#include<stdio.h>

main(){

	char ch;

	while(1){
	
		menu();
		printf("enter your choice(CODE):");
		scanf(" %c",&ch);
		if(ch == '0' || ch == 'x' || ch == 'X'){ /*come out of main loop*/
                                    char ext;
                                    printf("Are sure exit to main menu [y/n]: ");
                                    scanf(" %c",&ext);
                                    if(ext == 'y' || ext == 'Y')
                                                               return;
                                    if(ext == 'n' || ext == 'N')
                                                               continue;
                                    else
                                         continue;
			}

		menuHandler(ch);

	}
}

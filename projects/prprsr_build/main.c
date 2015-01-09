#include"get_line_hdr.c"
#include"comment.c"

main(int argc,char *argv[]){

        if(argc != 2){
                printf("Usage: %s <input_file>\n",argv[0]);
                exit(1);
                }

        int fd;
        char line[lSIZE];
        char hdr[hSIZE];
        char check[10];
        char dq;

        fd = open(argv[1],O_RDWR);

        while(Getline(fd,line)){ /*This while is for line iterations */
//                      printf("%s\n",line);
//		printf("main: %s\n",line);
		line_comment(line);
//                Gethdr(line,hdr);
                //printf("hdr: %s\n",hdr);

        }
i
}

//memory map io doesnt work for empty files.. and it assigns address of the content in the file to our dummy pointers(in bellow case char by char ) like as: in fd_r address of 1st char is mapped to address of 1st char in fd_w; then addrss of 2nd char in fd_r  to addrss of 2nd char in fd_w..
//so think if there is not enough char(data) in fd_w/fd_r its going to problem, but if mmap for empty file then BUS-ERROR occures.
// NOW ITS LIKE POINTERS, so u can write data into file only as much as the content is present in file, ie., actually by this, it is possible only overwriting the existed data only.
//ie., BY USING MMAP ONLY REPLACEMENT IS POSSIBLE(ie., only for existing data);

#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define SIZE _SIZE.st_size
main(){


/*HERE WE OPEN 2 FILES SOURCE(FOR READING ) AND DESTINATION(FOR WRITING)*/
int fd_r=open("text_rd.c",O_RDWR,0664); //no need of permissions 0776 becoz we are not creating a file. 
int fd_w=open("text_wr.c",O_RDWR|O_TRUNC|O_CREAT,0664);


/*HERE WE ARE USING A PRE-DEF FUNC STAT to obtain sizeof file in bytes coz that==no char in dat file */ //see man 2 stat.
struct stat _SIZE;
fstat(fd_r,&_SIZE);


/*CREATING A BUFF OF SIZE IS EQUALENT TO SIZE OF FILE to read total data at a time*/
char buff[SIZE];
int i;


/*BY THIS WE ARE CREATING THE WRITING FILE,AS REQIRED SIZE ie.,SIZE OF READING FILE by filling file with req num of char spaces.  SINCE BECOZ OF MEM-MAP I/O LIMITATIONS,IT CANNOT CREATE ACCESS IF THE FILE IS EMPTY */
for(i=0;i<SIZE;i++) write(fd_w," ",1);
syncfs(fd_w);// sync is must and shud becoz data must be dump at this instat olny otherwise "bus error" will come in mmap function, since we are not closing the file na??


/*printf("%ld\n",_SIZE.st_size);	//both gives same result, make lseek end position gives also file size in bytes.
printf("%d\n",lseek(fd_r,0,SEEK_END));*///Instead of finding size from predefined lib, we can use lseek also

/*CREATING MEMORY MAPPED IO FOR READING AND WRITING*/
	//read will done automatically, but write we have to assign the readed data each and every char by char
	//we are catching mmap return value to ptr to char since all files we are treating here is ascii (text based files).
char *rptr=mmap(NULL,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd_r,0);
char *wptr=mmap(NULL,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd_w,0);//WE CAN USE sizeof(buff) INSTEAD OF SIZE HERE;


for(i=0;i<sizeof(buff);i++)
	wptr[i]=rptr[i];       //here only we are writion into destination file happens. in above wptr allocation we are just allocate memory as size of read buff and each address of that is linked to our destination files up to SIZE chars. size is thats only it.
				//now those wptr addresses refer dest address, so by derefering them we can write data.
				// done as arrays with forloop. u can use *(wptr+i) instead of wptr[i];

munmap(rptr,SIZE);
munmap(wptr,SIZE);


close(fd_r);
close(fd_w);
}                                           //WORKS LIKE CPY FUNCTION

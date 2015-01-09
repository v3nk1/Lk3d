#include<stdio.h>
 struct msg {
        char str[20];
        int len;
   };

main(){
struct msg o[2]={{"venkat",strlen(o[0].str)},{"omkar",strlen(o[1].str)}},obj=o[1];
//obj=o[1];
printf("%s ==== %d\n",obj.str,obj.len);
}

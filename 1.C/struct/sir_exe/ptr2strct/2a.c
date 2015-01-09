#include<stdio.h>
 struct msg {
        char str[20];
        int len;
   };

main(){
struct msg o;//struct msg o={"i'm practicing",strlen(o.str)};
strcpy(o.str,"ven is practicing"); o.len=strlen(o.str);
printf("%s %d\n",o.str,o.len);
}    


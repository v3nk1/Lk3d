void at24_hexdel_keepchar(const char *src,char *dest){

        int i,j,k;
        for(k=0;k<16;k++)
                for(i=0,j=0;j<16;i=i+2,j++){
                        dest[j+k*16]=src[50+(k*82)+i];
                        }
}

main(){

	char b[]="41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q\n41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4f 50 51 | A B C D E F G H I J K L M O P Q";
	//printf("%s\n",b);
	char c[sizeof(b)];
	at24_hexdel_keepchar(b,c);
	c[sizeof(b)]=0;
	printf("%s\n",c);
}

#include<stdio.h>
//char str[27];
void
print (char ch)
{

  int i = 1, bi;
  char tmp;
  if (!((ch > 'A' && ch <= 'Z') || (ch > 'a' && ch <= 'z')))
    {
      printf ("%c\n", ch);
      return;
    }
  if (ch >= 'A' && ch <= 'Z')
    {
      tmp = 'A';
      int itr = (ch - tmp) + 1;
//      memset(str,' ',sizeof(str));
//      str[26]='\0';
//      printf ("itr: %i\n", itr);
      while (i != itr + 1)
	{
//         printf("################################################itr: %i,%i\n",itr,i);
	  while (tmp != ch)
	    {
	      printf ("%c ", tmp);
	      tmp++;
	    }
	  int k = 4 * (i - 1) - 1;	//i - 1;
	  if (k < 0)
	    k = 0;
	  i - 1 ? printf ("%c", tmp) : printf ("%c ", tmp--);
	  while (i - 1 && k--)
	    printf (" ");

	  while (tmp != 'A')
	    {
	      printf ("%c ", tmp);
	      tmp--;
	    }
	  printf ("%c", tmp);
	  printf ("\n");
	  i++;
	  ch--;
	}
    }
/*
	else if(ch>='a' && ch <='z'){
		tmp='a';
		while(tmp!=ch){
                        printf("%c",tmp);
                        tmp++;
                        }
                do{
                        printf("%c",tmp);
                        tmp--;
                        }while(tmp!='a');

		}
*/
}

main ()
{

  char ch;
  printf ("Enter a char: ");
  scanf (" %c", &ch);

  print (ch);

}

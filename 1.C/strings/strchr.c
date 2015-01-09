#include <stdio.h>
#include <string.h>
int main()
{
  // define some string
  char s[10] = "abcdefgh";
  // look for the character 'e' in the string s
  char *pos = strchr(s, 'e');
  // display search result
  if (pos)
    printf("Character 'e' found at position %d.\n", pos - s);
  else
    printf("Character 'e' not found.\n");
  return 0;
}

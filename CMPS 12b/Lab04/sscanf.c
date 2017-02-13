/* sscanf example */
#include <stdio.h>

int main ()
{
  char sentence []="12 Rudolph 12 is 12 years old";
  char str [20];
  int i;

  sscanf (sentence,"%s %*s %d",str,&i);
  printf ("%s -> %d\n",str,i);
  
  return 0;
}
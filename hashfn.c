#include <ctype.h>

int char2int( unsigned char c )
  // convert a printable character to an integer in the range 1-27.
{
  if ( isupper(c) )
  {
    return (int)(c-'A')+1;      // A=1, B=2, C=3, ..., Z=26
  }
  if ( islower(c) )
  {
    return (int)(c-'a')+1;      // a=1, b=2, c=3, ..., z=26
  }
  if ( isdigit(c) )
  {
    return (int)(c-'0')+27;	// 0=27, 1=28, 2=29, ..., 9=36
  }
  return 37;                    // anything else = 37
}

int hashfn( char *s, int max )
  // convert a string into a number between 0 and max (not inclusive)
{
  char *c;

  unsigned long number, column, new;

  // convert number to base 38 number
  number = 0;
  column = 1;
  for (c=s;(*c);c++)
  {
    number += char2int(*c) * column;
    column *= 38;
  }

  // convert number to a base max number and add up the column values
  new = 0;
  while (number)
  {
    new = (new + (number % max)) % max;
    number = number/max;
  }

  return (int)new;
}

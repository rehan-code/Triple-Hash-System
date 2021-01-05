/* util.c */

#include "util.h"


int read_key( FILE *fp, int index, char key[STRLEN] )
  // read the key string from a kv file
  // fp is a binary file opened for reading
  // index is the index of the key string to read
  // key is a string where the string will be returned
  // returns the result of the fread
{
  fseek( fp, 2*STRLEN*index, 0 );
  return fread( key, STRLEN, 1, fp );
}

int read_val( FILE *fp, int index, char val[STRLEN] )
  // read the value string from a kv file
  // fp is a binary file opened for reading
  // index is the index of the value string to read
  // val is a string where the string will be returned
  // returns the result of the fread
{
  fseek( fp, (STRLEN*2)*index+STRLEN, 0 );
  return fread( val, STRLEN, 1, fp );
}

int read_keyval( FILE *fp, char key[STRLEN], char val[STRLEN] )
{
  // read the key string and the value string from the current position in
  // a kv file
  // fp is a binary file opened for reading
  // key, val are strings where the strings will be returned
  // returns the result of the sum of the two freads, normally 2
  
  int retval = fread( key, STRLEN, 1, fp );
  retval += fread( val, STRLEN, 1, fp );
  return retval;
}

void write_empty( FILE *fp, long capacity )
  // write a hash file consisting of capacity -1 index values
{
  int index=-1;
  for (int i=0;i<capacity;i++)
    fwrite( &index, sizeof(int), 1, fp );
}

int get_capacity( FILE *fp )
{
  fseek( fp, 0, SEEK_END );
  return ftell(fp)/sizeof(int);
}

int write_index( FILE *fp, int index, int unsigned hash )
  // write index at the given hash_val in the hash (khs,vhs) file
{
  fseek( fp, hash*sizeof(int), SEEK_SET );
  return fwrite( &index, sizeof(int), 1, fp );
}

int read_index( FILE *fp, unsigned int hash, int *index )
  // read index from the given hash_val in the hash (khs,vhs) file
{
  fseek( fp, hash*sizeof(int), SEEK_SET );
  return fread( index, sizeof(int), 1, fp );
}


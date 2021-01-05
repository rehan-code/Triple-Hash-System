/* util.h */

#include <stdio.h>

#define STRLEN 256

int read_key( FILE *fp, int index, char key[STRLEN] );
int read_val( FILE *fp, int index, char val[STRLEN] );
int read_keyval( FILE *fp, char key[STRLEN], char val[STRLEN] );
void write_empty( FILE *fp, long size );
int get_capacity( FILE *fp );
int write_index( FILE *fp, int index, unsigned int hash_val );
int read_index( FILE *fp, unsigned int hash, int *index );

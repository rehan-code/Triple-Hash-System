#include "hashfn.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>


int main( int argc, char **argv ) {
    if (argc != 3) {//if wrong usage
        fprintf( stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
        exit(0);
    }
    
    FILE *fkv = fopen(argv[1],"rb");//pointer for kv file for reading

    //To initialize pointer to the vhs file
    char filename[strlen(argv[1])+2];//declaring filename to change the format

    strncpy(filename, argv[1], (strlen(argv[1])-2));
    filename[strlen(argv[1])-2] = '\0';
    strcat(filename, "vhs\0");//changing end to vhs file
    FILE *fvhs = fopen(filename,"rb");//pointer to vhs file for reading and writing

    long capacity = get_capacity(fvhs);//getting the capacity
    char key[STRLEN];
    char val[STRLEN];
    int ogHashIndex = hashfn(argv[2], capacity);
    int hashIndex = ogHashIndex;
    int normIndex;
    int cmpVal;

    do {
        read_index(fvhs, hashIndex, &normIndex);//find the index in the kv file
        read_val(fkv, normIndex, val);//get the key from the kv file
        cmpVal = strcmp(val,argv[2]);//cmp if the key is what we are looking for

        if (cmpVal != 0) {//if it isnt go to the next element
            if (hashIndex == capacity-1) {
                hashIndex = 0;
            } else {
                hashIndex++;
            }            
        }
    } while (cmpVal != 0 && hashIndex != ogHashIndex);//repeat while not found and has not looped back

    if (cmpVal == 0) {//if found
        read_key(fkv, normIndex, key);//find the corresponding key from the kv file
        printf("%s\n", key);//and print it
    } else {//if not found
        printf( "NOT FOUND\n" );//print not found
    }
    
    fclose(fkv);
    fclose(fvhs);

    return 1;
}
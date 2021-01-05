#include "hashfn.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>


int main( int argc, char **argv ) {
    if (argc != 3) {//if wrong usage
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]);
        exit(0);
    }
    //initializing pointer to the kv file
    long capacity = atoi(argv[2]);//storing capacity as a long
    FILE *fkv = fopen(argv[1],"rb");//pointer for kv file for reading
    
    //initialize pointer to the khs file
    char filename[strlen(argv[1])+2];//declaring filename to change the format

    strncpy(filename, argv[1], (strlen(argv[1])-2));
    filename[strlen(argv[1])-2] = '\0';
    strcat(filename, "khs\0");//changing end to khs file
    FILE *fkhs = fopen(filename,"wb+");//pointer to khs file for reading and writing
    
    //initialize pointer to the vhs file
    filename[strlen(filename)-3] = '\0';
    strcat(filename, "vhs\0");
    FILE *fvhs = fopen(filename,"wb+");//pointer to vhs file for reading and writing

    //intializing khs and vhs
    write_empty(fkhs, capacity);
    write_empty(fvhs, capacity);

    char key[STRLEN];
    char val[STRLEN];
    int index = -1;
    int i;
    int hashKey;
    int hashValue;

    while (read_keyval(fkv, key, val) == 2){//while it is not end of file (reads 2 elements each time)
        index++;
        hashKey = hashfn(key, capacity);
        hashValue = hashfn(val, capacity);
        
        i=index;
        read_index(fkhs, hashKey, &i);
        while (i != -1) {//while its not empty loop to the next element
            if (hashKey == capacity-1) {
                hashKey = 0;
            } else {
                hashKey++;
            }
            read_index(fkhs, hashKey, &i);//in case the next element is also not empty
        }
        write_index(fkhs, index, hashKey);//write the hash at the empty spot

        //repeat process for the vhs file
        i=index;
        read_index(fvhs, hashValue, &i);
        while (i != -1) {
            if (hashValue == capacity-1) {
                hashValue = 0;
            } else {
                hashValue++;
            }
            read_index(fvhs, hashValue, &i);
        }
        write_index(fvhs, index, hashValue);
    }

    fclose(fkv);
    fclose(fkhs);
    fclose(fvhs);

    return 1;
}
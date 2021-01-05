#include "hashfn.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>


int main( int argc, char **argv ) {
    if (argc != 2) {//if wrong usage
        fprintf( stderr, "Usage: %s 'movie name'\n", argv[0]);
        exit(0);
    }
    
    //opening all the pointers to the files we need
    FILE *fkvNameBasics = fopen("name.basics.kv","rb");//pointer for kv file for reading
    FILE *fkhsNameBasics = fopen("name.basics.khs","rb");//pointer to khs file for reading
    //FILE *fvhsNameBasics = fopen("name.basics.vhs","rb");//pointer to khs file for reading

    FILE *fkvTitleBasics = fopen("title.basics.kv","rb");//pointer for kv file for reading
    //FILE *fkhsTitleBasics = fopen("title.basics.khs","rb");//pointer to khs file for reading
    FILE *fvhsTitleBasics = fopen("title.basics.vhs","rb");//pointer to khs file for reading

    FILE *fkvTitlePrincipals = fopen("title.principals.kv","rb");//pointer for kv file for reading
    //FILE *fkhsTitlePrincipals = fopen("title.principals.khs","rb");//pointer to khs file for reading
    //FILE *fvhsTitlePrincipals = fopen("title.principals.vhs","rb");//pointer to khs file for reading

    
    long capacity = get_capacity(fvhsTitleBasics);//getting the capacity
    char key[STRLEN];
    char val[STRLEN];
    int ogHashIndex = hashfn(argv[1], capacity);
    int hashIndex = ogHashIndex;
    int normIndex;
    int cmpVal;

    //First we find the key of the movie name to search in the title.principals.kv file
    do {
        read_index(fvhsTitleBasics, hashIndex, &normIndex);//find the index in the kv file
        read_val(fkvTitleBasics, normIndex, val);//get the value from the kv file
        cmpVal = strcmp(val, argv[1]);//cmp if the value is what we are looking for
        
        if (cmpVal != 0) {//if it isnt go to the next element
            if (hashIndex == capacity-1) {
                hashIndex = 0;
            } else {
                hashIndex++;
            }            
        }
    } while (cmpVal != 0 && hashIndex != ogHashIndex);//repeat while not found and has not looped back
    
    if (cmpVal == 0) {//if found
        read_key(fkvTitleBasics, normIndex, key);//find the corresponding key from the kv file
    } else {//if not found
        printf( "NOT FOUND\n" );//print not found
        fclose(fkvNameBasics);
        fclose(fkhsNameBasics);
        fclose(fkvTitleBasics);
        fclose(fvhsTitleBasics);
        fclose(fkvTitlePrincipals);
        exit(0);
    }

    
    //then find all names codes corresponding to the title key to get the actor name
    normIndex = 0;
    char tempKey[STRLEN];
    char tempVal[STRLEN];
    int found = 0;

    while (read_keyval(fkvTitlePrincipals, tempKey, tempVal) == 2) {//while it is not end of file (reads 2 elements each time)
        if (strcmp(tempKey, key) == 0) {//If the movie title key matches
            found = 1;//found the movie name key in the title.principals file
            ogHashIndex = hashfn(tempVal, capacity);//get the hash of the actor name code
            hashIndex = ogHashIndex;
            //to search the names basic file to find the actors
            do {
                read_index(fkhsNameBasics, hashIndex, &normIndex);//find the index in the kv file
                read_key(fkvNameBasics, normIndex, tempKey);//get the key from the kv file
                cmpVal = strcmp(tempKey, tempVal);//cmp if the key corresponds to the actors code

                if (cmpVal != 0) {//if it isnt go to the next element
                    if (hashIndex == capacity-1) {
                        hashIndex = 0;
                    } else {
                        hashIndex++;
                    }
                }
            } while (cmpVal != 0 && hashIndex != ogHashIndex);//repeat while not found and has not looped back

            if (cmpVal == 0) {//if found
                read_val(fkvNameBasics, normIndex, val);//find the corresponding value from the kv file
                printf("%s\n", val);//and print it
            }
        }
    }//loop for all actors in the movie

    //closing all the file pointers
    fclose(fkvNameBasics);
    fclose(fkhsNameBasics);
    //fclose(fvhsNameBasics);

    fclose(fkvTitleBasics);
    //fclose(fkhsTitleBasics);
    fclose(fvhsTitleBasics);

    fclose(fkvTitlePrincipals);
    //fclose(fkhsTitlePrincipals);
    //fclose(fvhsTitlePrincipals);
    
    if (found == 0) {//if no actors found
        printf( "NOT FOUND\n" );//print not found
        return 0;
    }
    
    return 1;
}
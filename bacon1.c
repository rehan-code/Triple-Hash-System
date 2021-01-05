#include "hashfn.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>


int main( int argc, char **argv ) {
    if (argc != 2) {//if wrong usage
        fprintf( stderr, "Usage: %s 'actor name'\n", argv[0]);
        exit(0);
    }
    
    //opening all the pointers to the files we need
    FILE *fkvNameBasics = fopen("name.basics.kv","rb");//pointer for kv file for reading
    //FILE *fkhsNameBasics = fopen("name.basics.khs","rb");//pointer to khs file for reading
    FILE *fvhsNameBasics = fopen("name.basics.vhs","rb");//pointer to khs file for reading

    FILE *fkvTitleBasics = fopen("title.basics.kv","rb");//pointer for kv file for reading
    FILE *fkhsTitleBasics = fopen("title.basics.khs","rb");//pointer to khs file for reading
    //FILE *fvhsTitleBasics = fopen("title.basics.vhs","rb");//pointer to khs file for reading

    FILE *fkvTitlePrincipals = fopen("title.principals.kv","rb");//pointer for kv file for reading
    //FILE *fkhsTitlePrincipals = fopen("title.principals.khs","rb");//pointer to khs file for reading
    //FILE *fvhsTitlePrincipals = fopen("title.principals.vhs","rb");//pointer to khs file for reading

    
    long capacity = get_capacity(fvhsNameBasics);//getting the capacity
    char KBaconKey[STRLEN];
    char val[STRLEN];
    int ogHashIndex = hashfn("Kevin Bacon", capacity);
    int hashIndex = ogHashIndex;
    int normIndex;
    int cmpVal;
    //find the Key of the name Kevin Bacon
    do {
        read_index(fvhsNameBasics, hashIndex, &normIndex);//find the index in the kv file
        read_val(fkvNameBasics, normIndex, val);//get the value from the kv file
        cmpVal = strcmp(val, "Kevin Bacon");//cmp if the value found is 'Kevin Bacon'
        
        if (cmpVal != 0) {//if it isnt go to the next element
            if (hashIndex == capacity-1) {
                hashIndex = 0;
            } else {
                hashIndex++;
            }            
        }
    } while (cmpVal != 0 && hashIndex != ogHashIndex);//repeat while not found and has not looped back
    
    if (cmpVal == 0) {//if found
        read_key(fkvNameBasics, normIndex, KBaconKey);//find the corresponding key from the kv file
    } else {//if not found
        printf( "There is no Kevin Bacon in the title.basics files\n" );//print not found
        fclose(fkvNameBasics);
        fclose(fvhsNameBasics);
        //fclose(fkhsNameBasics);
        fclose(fkvTitleBasics);
        fclose(fkhsTitleBasics);
        //fclose(fvhsTitleBasics);
        fclose(fkvTitlePrincipals);
        exit(0);
    }

    
    //Find the key for the actor name given from argument 1
    normIndex = 0;
    char actorKey[STRLEN];
    ogHashIndex = hashfn(argv[1], capacity);
    hashIndex = ogHashIndex;

    do {
        read_index(fvhsNameBasics, hashIndex, &normIndex);//find the index in the kv file
        read_val(fkvNameBasics, normIndex, val);//get the key from the kv file
        cmpVal = strcmp(val,argv[1]);//cmp if the key is what we are looking for

        if (cmpVal != 0) {//if it isnt go to the next element
            if (hashIndex == capacity-1) {
                hashIndex = 0;
            } else {
                hashIndex++;
            }            
        }
    } while (cmpVal != 0 && hashIndex != ogHashIndex);//repeat while not found and has not looped back

    if (cmpVal == 0) {//if found
        read_key(fkvNameBasics, normIndex, actorKey);//find the corresponding key from the kv file
    } else {//if not found
        printf( "ACTOR NOT FOUND\n" );//print not found
        fclose(fkvNameBasics);
        fclose(fvhsNameBasics);
        //fclose(fkhsNameBasics);
        fclose(fkvTitleBasics);
        fclose(fkhsTitleBasics);
        //fclose(fvhsTitleBasics);
        fclose(fkvTitlePrincipals);
        exit(0);
    }


    char movieKey[STRLEN];
    char movieName[STRLEN];
    char tempKey[STRLEN];
    char tempKey2[STRLEN];
    char tempval[STRLEN];
    int i, j;

    for (i = 0; i < capacity-1 && read_val(fkvTitlePrincipals, i, val) == 1; i++) {//it will check the whole title.pricipals list
        //read_val(fkvTitlePrincipals, i, val);//get the actor code
        if (strcmp(val, actorKey) == 0) {//check if its the actor we are looking for
            read_key(fkvTitlePrincipals, i, movieKey);//get the movie key to chek if Kevin Bacon is in it
            for (j = 0; j < capacity-1 && read_key(fkvTitlePrincipals, j, tempKey) == 1; j++) {//check the whole list for the movie key
                //read_key(fkvTitlePrincipals, j, tempKey);//get the temp movie key
                if (strcmp(tempKey, movieKey) == 0) {//if its the same movie with the actor were looking for
                    read_val(fkvTitlePrincipals, j, tempval);//get the temp actor
                    if (strcmp(tempval, KBaconKey) == 0) {//check if its Kevin bacon
                        //get the movie name to print
                        ogHashIndex = hashfn(movieKey, capacity);//hash the movie key to search for it
                        hashIndex = ogHashIndex;

                        do {
                            read_index(fkhsTitleBasics, hashIndex, &normIndex);//find the index in the kv file
                            read_key(fkvTitleBasics, normIndex, tempKey2);//get the key from the kv file
                            cmpVal = strcmp(tempKey2,movieKey);//cmp if its the movie key we are looking for

                            if (cmpVal != 0) {//if it isnt go to the next element
                                if (hashIndex == capacity-1) {
                                    hashIndex = 0;
                                } else {
                                    hashIndex++;
                                }
                            }
                        } while (cmpVal != 0 && hashIndex != ogHashIndex);//repeat while not found and has not looped back

                        if (cmpVal == 0) {//if found
                            read_val(fkvTitleBasics, normIndex, movieName);//find the corresponding value (movie name) from the kv file
                            printf("%s\n", movieName);//and print it
                        } else {//if not found
                            printf( "MOVIE TITLE NOT FOUND\n" );//print not found
                        }
                        fclose(fkvNameBasics);
                        fclose(fvhsNameBasics);
                        //fclose(fkhsNameBasics);
                        fclose(fkvTitleBasics);
                        fclose(fkhsTitleBasics);
                        //fclose(fvhsTitleBasics);
                        fclose(fkvTitlePrincipals);
                        return 1;
                    }   
                }
                
            }
            
        }
        
    }
    

    //closing all the file pointers
    fclose(fkvNameBasics);
    //fclose(fkhsNameBasics);
    fclose(fvhsNameBasics);

    fclose(fkvTitleBasics);
    fclose(fkhsTitleBasics);
    //fclose(fvhsTitleBasics);

    fclose(fkvTitlePrincipals);
    //fclose(fkhsTitlePrincipals);
    //fclose(fvhsTitlePrincipals);
    
    return 0;
}
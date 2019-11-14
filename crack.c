#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN=20;        // Maximum any password will be
const int HASH_LEN=33;        // Length of MD5 hash strings

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    char* hashed_guess;
    hashed_guess=md5(guess, strlen(guess));
    if(strcmp(hashed_guess,hash)==0){
        free(hashed_guess);
       // printf("Hello\n");//test code
        return 1;
    }
 //   printf("%s %s %s Oh\n",hashed_guess, guess, hash);//test code
    free(hashed_guess);
    return 0;
}

// Read in the dictionary file and return the array of strings
// and store the length of the array in size.
// This function is responsible for opening the dictionary file,
// reading from it, building the data structure, and closing the
// file.
char **read_dictionary(char *filename, int *size)
{   int count=0;
    FILE *f=fopen(filename,"r");
    int lines=50;
    char **dictionary=malloc(lines*sizeof(char *));
    char line[1000];
    while (fgets(line,1000,f)!=NULL){
        if(count==lines){
            lines+=50;
            dictionary=realloc(dictionary,lines*sizeof(char*));
        }
    
        line[strlen(line)-1]='\0';
        char *word=malloc(strlen(line)*sizeof(char)+1);
        strcpy(word,line);
        dictionary[count]=word;
        count++;}
    *size = count;
    fclose(f);
    return dictionary;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Read the dictionary file into an array of strings.
    int dlen;
    char **dict = read_dictionary(argv[2], &dlen);

    // Open the hash file for reading.
    FILE *hash_file=fopen(argv[1],"r");
    

    // For each hash, try every entry in the dictionary.
    // Print the matching dictionary entry.
    // Need two nested loops.
    
    char line[1000]; /*
    for (int i=0;i<dlen;i++){
        while(fgets(line,1000,hash_file)!=NULL){
            line[strlen(line)-1]='\0'; //replace newline on hash with a null character
            if((tryguess(line,dict[i]))==1){
                printf("%s %s \n",line, dict[i]);
            }
            printf("%s %s why?\n",line, dict[i]); //test code
            
        }
    }*/
    
    while(fgets(line,1000,hash_file)!=NULL){
        line[strlen(line)-1]='\0'; //replace newline on hash with a null character
        for(int i=0;i<dlen;i++){
            if((tryguess(line,dict[i]))==1){
                printf("%s %s \n",line, dict[i]);
            }
          //  printf("%s %s why?\n",line, dict[i]); //test code
            
        }
    }
    //printf("%d\n",dlen); //test code
}

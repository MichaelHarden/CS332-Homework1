//
//  main.c
//  Keyword_Text_Search-hw1
//
//  Created by Michael Harden on 1/16/22.
//
//  Demoed with Grant at lab 3 on 1/28/22.
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring Functions
struct SearchKey* parseKeysToArray(const char* argv[], int n);
struct SearchKey makeKey(const char* key);

char** tokenize(char* string, int* n_of_tokens);

/* A SearchKey is an object which will hold a key, and the number of
 occurrences of that key. When searching a text input, every time the key is
 seen, the frequency will increment by 1
 */
struct SearchKey {
    const char* key;
    int frequency;
};


/* main */
int main(int argc, const char* argv[]) {
    // Parses the command line arguements to an array of SearchKeys.
    struct SearchKey* keys = parseKeysToArray(argv, argc);
   
    //Read in user input text
    char* input = (char*)malloc(0);
    size_t size = 0;
    ssize_t n;
    
    
    do {
        char* temp_store = NULL;
        // get line will store the text into input
        n = getline(&temp_store, &size, stdin);
        strcat(input, temp_store);
    } while (n > 0);    // check no characters have been passed to to temp_storage
    
    // tokens is an array of strings storing the input text, post tokenization.
    int n_of_tokens;
    char** tokens = tokenize(input, &n_of_tokens);
    
    // for every token, check if it is equal to any of the search keys
    int i, j;
    for(i = 0; i< n_of_tokens; i++) {
        for (j=0; j < argc-1; j++) {
            if( !(strcmp(tokens[i], keys[j].key))) {
                keys[j].frequency++;

            }
        }
    }
    
    // print the each key and its occurance.
    for (i = 0; i < argc-1; i++) {
        printf("%s: %d\n", keys[i].key, keys[i].frequency);
    }
    return 0;
}


/* The tokenize method takes a string and will tokenize it based on space or
period delimiters.

Parameters:
    char* string: the text to tokenize
    int* n_of_tokens: updates the number of tokens as a new token is found.
                        (passing by reference allows for the number of tokens
                        to not need to be returned.)
 
 Return:
    An array of strings, where each string is the tokens.
 
 */
char** tokenize(char* string, int* n_of_tokens) {
    // allocate memory on heap for token list
    int size = 10;
    char** tokens = (char**)malloc(size * sizeof(char*));
    *n_of_tokens = 0;

    //gets the first token
    char* tok = strtok(string, " .\n");

    // when at the end of the string, the strtok method will return a NULL
    // pointer. So this is our break condition for the while loop
    int i = 0;
    while ( tok != NULL ) {
        //storing the token
        tokens[i] = tok;
        (*n_of_tokens)++;
        i++;
        
        // if the array runs out of storage, then the size of the array is doubled
        if (*n_of_tokens >= size ) {
            size *= 2;
            tokens = (char**)realloc(tokens, size * sizeof(char*));
        }
        
        // get the next token
        tok = strtok(NULL, " .\n");
    }
    return tokens;
}

/* parseKeyToArray will take an array of strings, and parse them into an array of SearchKeys
 
 Parameters:
    const char* argv[]: passing in the command line arguments
    int n: number of strings in argv[]
 
 Return:
    returns an array of SearchKeys
 */
struct SearchKey* parseKeysToArray(const char* argv[], int n) {
    int i;
    // memory is created dynamically
    struct SearchKey* keys = (struct SearchKey*) malloc( sizeof(struct SearchKey));
    for (i = 1; i < n; i++) {
        keys[i-1] = makeKey(argv[i]); // start at index 1, due to the first command line arg is the file name
    }
    return keys;
}


/* makeKey takes a string and creates and returns a SearchKey for that word. */
struct SearchKey makeKey(const char* key) {
    struct SearchKey searchKey;
    searchKey.key = key;
    searchKey.frequency = 0;
    
    return searchKey;
}



#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 

#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS
#include "file_operations.c"
#endif

#ifndef PTHREAD_IMPORT
#define PTHREAD_IMPORT
#include <pthread.h>
#endif


#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
  
// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (224) //224 - 93

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)' ') 

#define DEFAULT_OUTPUT_NAME "output.txt"

struct node{
    int ocurrence;
    struct node **nexts;
};

struct node *create_empty_node(void){
    struct node *pNode = NULL; 
    pNode = (struct node *)malloc(sizeof(struct node));
    if (pNode) 
    { 
        int i;
        pNode->ocurrence = 0;
        pNode->nexts = malloc(sizeof(struct node *) * ALPHABET_SIZE);
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->nexts[i] = NULL; 
    }
    return pNode;
}

void insert(struct node *root, const unsigned char *key){
    
    int level;
    int length = strlen(key);
    int index;
    struct node *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if ( !pCrawl->nexts[index] ) 
            pCrawl->nexts[index] = create_empty_node();
        
        pCrawl = pCrawl->nexts[index];
    }
    pCrawl->ocurrence++; 
}
void insert_with_ocurrence(struct node *root, const unsigned char *key, int oc){
    
    int level;
    int length = strlen(key);
    int index;
    struct node *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if ( !pCrawl->nexts[index] ) 
            pCrawl->nexts[index] = create_empty_node();
        
        pCrawl = pCrawl->nexts[index];
    }
    pCrawl->ocurrence += oc; 
}


int search(struct node *r, const char *key){
    int level;
    int length = strlen(key);
    int index;
    struct node *pCrawl = r;
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->nexts[index]) 
            return false; 
  
        pCrawl = pCrawl->nexts[index]; 
    } 
    if((pCrawl != NULL && pCrawl->ocurrence > 0))
        return pCrawl->ocurrence;
    else if(pCrawl != NULL)
        return 0;//NOPE non existent
    else
        return -1; //-1 is error, if something terrible happens, this is it
}

// function to display the content of Trie 
void display(struct node* root, char str[], int level, FILE *f) 
{ 
    // If node is leaf node, it indicates end 
    // of string, so a null character is added 
    // and string is displayed 
    if (root->ocurrence && root->ocurrence > 0)  
    {
        str[level] = '\0';
        //printf("%s %d\n", str, root->ocurrence);
        //it should be written to the output file around here.
        update_output_file(str, root->ocurrence,f);

    } 
  
    int i; 
    for (i = 0; i < ALPHABET_SIZE; i++)  
    { 
        // if NON NULL child is found 
        // add parent key to str and 
        // call the display function recursively 
        // for child node 
        if (root->nexts[i])  
        { 
            str[level] = i + ' ';
            display(root->nexts[i], str, level + 1, f);
        } 
    }
}

void free_trie_allocation(struct node* root){
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        if(root->nexts[i])
            free_trie_allocation(root->nexts[i]);
    }
    free(root->nexts);
    free(root);
}
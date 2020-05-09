#ifndef LIBRARY_IMPORTS
#define LIBRARY_IMPORTS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#endif

#ifndef TRIE_C
#define TRIE_C
#include "../trie.c"
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 9999
#endif

/**
 * Task 3 : Sequential with Multiple Queries
 * 1- Read n chars from the file
 * 2- Find how many lines you have read (\n count is enough ?)
 * 3- Move the file pointer to the last \n so that lines wont be half
 * 4- For each line item, insert it to the trie
 * 5- Repeat 1-4 until all input files are done
 * 6- Insert all trie items to output file
 * 
 * OBSERVE EXECUTION TIME
 */
void task3(char *data[])
{
    char buffer[BUFFER_LENGTH];


}
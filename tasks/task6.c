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
 * Task 6
 * Similar to Task 2 and 3.
 * 
 * 1- For each input file, read ALL of the queries to memory
 * 2- NO THREADS
 * 3- Insert each query (that is in the memory) to trie
 * 4- Write to output file
 * 5- OBSERVE EXECUTION TIME
 * 
 * Idea is code will only use disk access once, 
 * so there may be a speed-up in execution time
 */
void task6(char *data[], int data_size)
{
    
}
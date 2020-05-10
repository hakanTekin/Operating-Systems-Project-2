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
 * Task 5
 * Similar to Task 4, each thread has its own Trie tho
 * 
 * After each thread completes its own execution,
 * These tries are merged into one
 * 
 * After merging, put to output file.
 * 
 * OBSERVE EXECUTION TIME
 * 
 */
void task5(char *data[], int data_size)
{}
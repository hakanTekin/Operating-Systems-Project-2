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
 * Task 4: Threaded Execution
 * Same as task 2, but each input file is processed in its own thread
 * There is a single trie, each process puts its result to this trie
 * 
 * The insertions should be concurrent. So there may be errors during execution
 * Observe the errors
 * 
 * Use mutexes so that access from multiple therads will be prevented
 * 
 * OBSERVE EXECUTION TIME
 */
void task4(char *data[])
{}
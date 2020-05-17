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

#define DEFAULT_OUTPUT_NAME_TASK_6 "output_6.txt"

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
    FILE *fptr;
    struct node *root = malloc(sizeof(struct node));
    unsigned char *line_buffer;
    char *buffer = NULL;
    for (size_t i = 0; i < data_size; i++)
    {
        //Open the file and find its size
        fptr = open_file_from_file_name(data[i], "r");
        if (fptr)
        {
            fseek(fptr, 0L, SEEK_END);
            int sz = ftell(fptr);
            rewind(fptr);
            //Create a buffer size of contents of the file
            char *buffer = malloc(sz * sizeof(char));
            fread(buffer, 1, sz, fptr);

            line_buffer = strtok(buffer, "\n");

            while (line_buffer != NULL)
            {
                insert(root, line_buffer);
                line_buffer = strtok(NULL, "\n");
            }
        }
        else
            printf("Could not open file.\n");
    }
    char line_buffer_2[9999];
    FILE *output = open_file_from_file_name(DEFAULT_OUTPUT_NAME_TASK_6, "w+");
    display(root, line_buffer_2, 0, output);
    //free buffer
    free(buffer);
    free(line_buffer);
    free_trie_allocation(root);
}
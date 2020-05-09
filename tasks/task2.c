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
 * Task 2 method
 * 1- Reades line by line from the input file(s)
 * 2- Add the current line to trie
 * 3- Repeat 1-2
 * 4- Read trie by tree traversal
 * 5- For each item in the trie, add it to the output file
 * 
 *  OBSERVE EXECUTION TIME
 */
void task2(char *data[])
{
    struct node *root = create_empty_node();

    FILE *in_file;
    FILE *out_file;
    char buffer[9999];
    for (size_t i = 0; i < 1; i++)
    {
        in_file = open_file_from_file_name(data[i], NULL);
        if(in_file != NULL){
            char *temp;
            while(fgets(buffer, 9999, in_file)){
                remove_new_line_from_str(buffer);
                insert(root, buffer);
            }
        }
        else
            printf("%s could not be opened\n", data[i]);
    }
    out_file = open_file_from_file_name(DEFAULT_OUTPUT_NAME, "w");
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        if(buffer[i] != '\0')
            buffer[i] = '\0';
        else
            break;
    }
    printf("%d\n", search(root, "pantina"));
    display(root, buffer, 0, out_file);
    fclose(in_file);
}
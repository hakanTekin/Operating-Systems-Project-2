#ifndef LIBRARY_IMPORTS
#define LIBRARY_IMPORTS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#endif

#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS
#include "../file_operations.c"
#endif

#ifndef TRIE_C
#define TRIE_C
#include "../trie.c"
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 100
#endif

#define DEFAULT_OUTPUT_NAME_TASK_3 "output_3.txt"
/**
 * Task 3 : Sequential with Multiple Queries
 * 1- Read n chars from the file
 * 2- Find how many lines you have read (\n count is enough ?)
 * 3- Move the file pointer to the last \\n so that lines wont be half
 * 4- For each line item, insert it to the trie
 * 5- Repeat 1-4 until all input files are done
 * 6- Insert all trie items to output file
 * 
 * OBSERVE EXECUTION TIME
 */

FILE **f;
int size_of_data;
void open_files(char *data[], int *f_array_count){
    
    f = (FILE **)malloc(sizeof(FILE) * size_of_data);
    
    for (size_t i = 0; i < size_of_data; i++)
    {
        FILE *file = malloc(sizeof(FILE));
        file = fopen(data[i], "r");
        if(file != NULL){
            f[*f_array_count++] = file;

        }
    }
}
void task3(char *data[])
{
    char buffer[BUFFER_LENGTH+1];
    size_of_data = sizeof(data) / sizeof(data[0]);
    int f_array_size = 0;
    open_files(data, &f_array_size);

    struct node *root = create_empty_node();

    for (size_t i = 0; i < size_of_data; i++)
    {
        while( 1 ){
            size_t x = fread( buffer, 1, BUFFER_LENGTH, f[i] );
            if(x == 0)
                break;
            if(x != BUFFER_LENGTH || x == EOF)
                buffer[x] = '\0';
            int new_line_count = 0;
            char *last_new_line;
            char *Start = &buffer[0];
            char temp[9999] = {'\0'};
            printf("%d\n", strlen(buffer));

            /**
             * TODO: This is an extremely inefficent way to iterate,
             * Find a better way that will skip the unsuiting chars (not \n or \0)
             * Instead of iterating one by one 
            */
            for (size_t j = 0; j <= strlen(buffer); j++)
            {
                if(buffer[j] == '\n' || buffer[j] == '\0'){
                    new_line_count++;
                    last_new_line = &buffer[j];
                    strncpy(temp, Start, last_new_line-Start);
                    temp[last_new_line-Start] = '\0';
                    printf("%s\n", temp);
                    Start = last_new_line+1;
                    insert(root, temp);
                }
            }
            if(strlen(buffer) == 9999){
                printf("%p\n", &buffer[strlen(buffer)] );
                fseek(f[i], -(&buffer[strlen(buffer)] - last_new_line)+1, SEEK_CUR);
            }
        }
        fclose(f[i]);
    }
    FILE *out_file = open_file_from_file_name(DEFAULT_OUTPUT_NAME_TASK_3, "w");
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        if(buffer[i] != '\0')
            buffer[i] = '\0';
        else
            break;
    }
    display(root, buffer, 0, out_file);
    fclose(out_file);
}
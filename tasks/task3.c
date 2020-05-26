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
    int x = 0;
    for (size_t i = 0; i < size_of_data; i++)
    {
        FILE *file = malloc(sizeof(FILE));
        file = fopen(data[i], "r");
        if(file != NULL){
            f[x++] = file;

        }
    }
    *f_array_count = x;
}

void do_with_char(char buffer[], int i, struct node *root){
    while( 1 ){
            size_t x = fread( buffer, 1, BUFFER_LENGTH, f[i] );
            if(x == 0)
                break;
            if(x != BUFFER_LENGTH || x == EOF)
                buffer[x] = '\n';
                buffer[x+1] = '\0';
            int new_line_count = 0;
            char *last_new_line;
            char *Start = &buffer[0];
            unsigned char temp[9999] = {'\0'};
            /**
             * TODO: This is an extremely inefficent way to iterate,
             * Find a better way that will skip the unsuiting chars (not \n or \0)
             * Instead of iterating one by one 
            */
            for (size_t j = 0; j <= strlen(buffer); j++)
            {
                if(buffer[j] == '\n'){
                    new_line_count++;
                    last_new_line = &buffer[j];
                    strncpy(temp, Start, last_new_line-Start);
                    temp[last_new_line-Start] = '\0';
                    //printf("%s\n", temp);
                    Start = last_new_line+1;
                    insert(root, temp);
                }
            }
            if(strlen(buffer) == 9999){
                //printf("%p\n", &buffer[strlen(buffer)] );
                fseek(f[i], -(&buffer[strlen(buffer)] - last_new_line)+1, SEEK_CUR);
            }
        }
        fclose(f[i]);
}


void do_with_fgets(int i, struct node *root){
    int count = 0;
    char buffer[BUFFER_LENGTH+5000];
    char sub_buffer[BUFFER_LENGTH+5000];
    int break_val = 0;
    char last_buffer[4950]; //is for the last half line that has not been read by fread
    while(break_val == 0){
        int read_count = fread(buffer, 1, BUFFER_LENGTH+1, f[i]); //+1 because the last termination character
        buffer[read_count] = '\0';
        if(read_count == BUFFER_LENGTH+1){ //Then file has not yet ended
            if(!fgets(last_buffer, 4900, f[i])) //Gets until the last new line or EOF) //File has been ended*
                break_val = 1;
            strcat(buffer, last_buffer);
        }else
            break_val = 1;
        char *single_line = strtok(buffer, "\n");
        while (single_line != NULL){
            if(strcmp(single_line, "zirconial crowns") == 0){
                printf("ha\n");
            }
            insert(root, single_line);
            single_line = strtok(NULL, "\n");
        }
        count++;
    }
    printf("KEKKO\n");
    fclose(f[i]);
    printf("E ebesinin ami\n");
}

void task3(char *data[], int data_size)
{
    char buffer[BUFFER_LENGTH+1];
    size_of_data = data_size;
    int f_array_size = 0;
    open_files(data, &f_array_size);

    struct node *root = create_empty_node();

    for (size_t i = 0; i < f_array_size; i++)
    {
        //do_with_char(buffer, i, root);
        do_with_fgets(i, root);
    }

    FILE *out_file = open_file_from_file_name(DEFAULT_OUTPUT_NAME_TASK_3, "w");
    display(root, buffer, 0, out_file);
    fclose(out_file);

    free_trie_allocation(root);
}
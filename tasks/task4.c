#ifndef LIBRARY_IMPORTS
#define LIBRARY_IMPORTS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#endif

#ifndef PTHREAD_IMPORT
#define PTHREAD_IMPORT
#include <pthread.h>
#endif

#ifndef TRIE_C
#define TRIE_C
#include "../trie.c"
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 9999
#endif

#define DEFAULT_OUTPUT_NAME_TASK_4 "output_4.txt"


#ifndef ARGS_STRUCT
#define ARGS_STRUCT

struct args_struct
{
    char file_name[500];
    struct node *n;
};

#endif

pthread_mutex_t mutex_lock;

void *apply_threaded_task_4(void *a)
{
    struct args_struct *args = (struct args_struct *)a;
    char *file_name = args->file_name;
    struct node *root = args->n;
    unsigned char buffer[BUFFER_LENGTH];
    FILE *in_file;
    in_file = open_file_from_file_name(file_name, NULL);
    if (in_file != NULL)
    {
        char *temp;
        while (fgets(buffer, BUFFER_LENGTH, in_file))
        {
            remove_new_line_char_from_str(buffer);
            //insert(root, buffer);
            pthread_mutex_lock(&mutex_lock);
            insert(root, buffer);
            pthread_mutex_unlock(&mutex_lock);
        }
    }
    else
        printf("%s could not be opened\n", file_name);

     printf("A THREAD IS COMPLETED\n");
}

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
void task4(char *data[], int data_length)
{

    if(pthread_mutex_init(&mutex_lock, NULL) != 0){
        printf("Mutex init failed\n");
        return;
    }
    struct node *root = create_empty_node();

    FILE *in_file;
    FILE *out_file;
    char buffer[BUFFER_LENGTH];


    //There should be as much threads as there are files in data array
    pthread_t **threads = malloc(sizeof(pthread_t) * data_length);
    size_t threads_count = 0; //This works as index to the threds array
    for (size_t i = 0; i < data_length; i++)
    {
        struct args_struct *args = malloc(sizeof(struct args_struct));
        strcpy(args->file_name, data[i]);
        args->n = root;

        pthread_create(&threads[threads_count++], NULL, apply_threaded_task_4, args);
        printf("ONE THREAD CREATED BEFORE THIS WAS PRINTED\n");
    }
    
    for (int j = 0; j < threads_count; j++)
    {
        pthread_join(threads[j], NULL);
        printf("I wait is end for thread\n");
    }

    printf("THIS SHOULD NOT BE REACHED BEFORE ALL THE THREADS ARE DONE\n");

    out_file = open_file_from_file_name(DEFAULT_OUTPUT_NAME_TASK_4, "w");
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] != '\0')
            buffer[i] = '\0';
        else
            break;
    }
    display(root, buffer, 0, out_file);
    if(fclose(out_file)){
        printf("error closing fil \n");
        exit(-1);
    }else{
        printf("Hahahha\n");
    }

    free_trie_allocation(root);
}
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


#define DEFAULT_OUTPUT_NAME_TASK_5 "output_5.txt"

#ifndef ARGS_STRUCT
#define ARGS_STRUCT

struct args_struct
{
    char file_name[500];
    struct node *n;
};

#endif

pthread_mutex_t mutex_lock;


void *apply_threaded_task_5(void *a)
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

void converge_to_main_root(struct node *root, char str[], int level, struct node *main_root){
    // If node is leaf node, it indicates end 
    // of string, so a null character is added 
    // and string is displayed 
    if (root->ocurrence > 0)  
    {
        str[level] = '\0';
        //printf("%s %d\n", str, root->ocurrence);
        //it should be written to the output file around here.
        insert_with_ocurrence(main_root, str, root->ocurrence);

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
            converge_to_main_root(root->nexts[i], str, level + 1, main_root);
        } 
    }
}

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
void task5(char *data[], int data_length)
{

    if(pthread_mutex_init(&mutex_lock, NULL) != 0){
        printf("Mutex init failed\n");
        return ;
    }
    struct node *main_root = create_empty_node();

    FILE *in_file;
    FILE *out_file;
    char buffer[BUFFER_LENGTH];

    struct node **roots = (struct node **) malloc(sizeof(struct args_struct) * data_length);
    if(roots == NULL){
        printf("ROOTS IS NULL\n");
        return ;
    }

    //There should be as much threads as there are files in data array
    pthread_t **threads = malloc(sizeof(pthread_t) * data_length);
    size_t threads_count = 0; //This works as index to the threds array
    for (size_t i = 0; i < data_length; i++)
    {
        struct args_struct *args = malloc(sizeof(struct args_struct));
        strcpy(args->file_name, data[i]);
        roots[i] = create_empty_node();
        args->n = roots[i];

        pthread_create(&threads[threads_count++], NULL, apply_threaded_task_5, args);
        printf("ONE THREAD CREATED BEFORE THIS WAS PRINTED\n");
    }
    
    for (int j = 0; j < threads_count; j++)
    {
        pthread_join((pthread_t *)threads[j], NULL);
        printf("I wait is end for thread\n");
    }

    printf("THIS SHOULD NOT BE REACHED BEFORE ALL THE THREADS ARE DONE\n");

    out_file = open_file_from_file_name(DEFAULT_OUTPUT_NAME_TASK_5, "w");
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] != '\0')
            buffer[i] = '\0';
        else
            break;
    }
    printf("%d\n", data_length);

    for (size_t i = 0; i < data_length; i++)
        converge_to_main_root(roots[i], buffer, 0, main_root);
    

    display(main_root, buffer, 0, out_file);

    if(fclose(out_file)){
        printf("error closing fil \n");
        exit(-1);
    }else{
        printf("Hahahha\n");
    }

    for (size_t i = 0; i < data_length ; i++)
        free_trie_allocation(roots[i]);
    
    free_trie_allocation(main_root);
}
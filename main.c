#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef TRIE_C
#define TRIE_C
#include "trie.c"
#endif

#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS
#include "file_operations.c"
#endif


#ifndef TASK_INCLUDES
#define TASK_INCLUDES
#include "tasks/task2.c"
#include "tasks/task3.c"
#include "tasks/task4.c"
#include "tasks/task5.c"
#include "tasks/task6.c"
#include "tasks/task7.c"
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 100
#endif

//Names of the input files, this could be changed to an command line argument tho.
char *data[] = {"data-6.txt", "data-7.txt"};
int data_size = sizeof(data) / sizeof(data[0]);

void remove_new_line_char_from_str(char *str){
    char *temp = strchr(str, '\n');
    if(temp != NULL){
        *temp = '\0';
    }
}
int main()
{
    clock_t start2 = clock();
    //task2(data, data_size);
    clock_t end2 = clock();

    printf("TASK 2 FINISHED\n");

    clock_t start3 = clock();
    //task3(data, data_size);
    clock_t end3 = clock();

    printf("TASK 3 FINISHED\n");

    clock_t start4 = clock();
    task4(data, data_size);
    clock_t end4 = clock();

    printf("TASK 4 FINISHED\n");

    clock_t start5 = clock();
    task5(data, data_size);
    clock_t end5 = clock();

    clock_t start6 = clock();
    task6(data, data_size);
    clock_t end6 = clock();

    printf("\n---All executions completed---\n");

    printf("%-40s : %-20d\n", "Task2 Execution time", end2-start2);
    printf("%-40s : %-20d\n", "Task3 Execution time", end3-start3);
    printf("%-40s : %-20d\n", "Task4 Execution time", end4-start4);
    printf("%-40s : %-20d\n", "Task5 Execution time", end5-start5);
    printf("%-40s : %-20d\n", "Task6 Execution time", end6-start6);

    return 4000;
}
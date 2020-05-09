#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef TRIE_C
#define TRIE_C
#include "trie.c"
#endif

#ifndef TASK_INCLUDES
#define TASK_INCLUDES
#include "tasks/task1.c"
#include "tasks/task2.c"
#include "tasks/task3.c"
#include "tasks/task4.c"
#include "tasks/task5.c"
#include "tasks/task6.c"
#include "tasks/task7.c"
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 9999
#endif

void remove_new_line_from_str(char *str){
    char *temp = strchr(str, '\n');
    if(temp != NULL){
        *temp = '\0';
    }
}

/**
 * Task 3 : Sequential with Multiple Queries
 * 1- Read n chars from the file
 * 2- Find how many lines you have read (\n count is enough ?)
 * 3- Move the file pointer to the last \n so that lines wont be half
 * 4- For each line item, insert it to the trie
 * 5- Repeat 1-4 until all input files are done
 * 6- Insert all trie items to output file
 * 
 * OBSERVE EXECUTION TIME
 */
void task3()
{
    char buffer[BUFFER_LENGTH];

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
void task4()
{}

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
void task5()
{}

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
void task6()
{}

/**
 * Task 7
 * 
 * Improve one of the above methods
 * According to their execution times
 */
void task7()
{

}

int main()
{
    clock_t start2 = clock();
    task2();
    clock_t end2 = clock();

    clock_t start3 = clock();
    task3();
    clock_t end3 = clock();

    clock_t start4 = clock();
    task4();
    clock_t end4 = clock();

    clock_t start5 = clock();
    task5();
    clock_t end5 = clock();

    clock_t start6 = clock();
    task6();
    clock_t end6 = clock();

    printf("\n---All executions completed---\n");

    printf("%-40s : %-20d\n", "Task2 Execution time", end2-start2);
    printf("%-40s : %-20d\n", "Task3 Execution time", end3-start3);
    printf("%-40s : %-20d\n", "Task4 Execution time", end4-start4);
    printf("%-40s : %-20d\n", "Task5 Execution time", end5-start5);
    printf("%-40s : %-20d\n", "Task6 Execution time", end6-start6);

    return 0;
}
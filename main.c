#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tasks/task1.c>
#include <tasks/task2.c>
#include <tasks/task3.c>
#include <tasks/task4.c>
#include <tasks/task5.c>
#include <tasks/task6.c>
#include <tasks/task7.c>

#include <trie.c>
#include <file_operations.c>

int main(){
    
    char data[] = {"data0.txt"};
    struct node *root = create_empty_node();

    FILE *f;
    char buffer[9999];
    
    //
    for (size_t i = 0; i < 1; i++)
    {
        f = open_file_from_file_name(data[i], NULL);
        if(f != NULL)
            while(fgets(buffer, 9999, f))
                insert(root, buffer);
        else
            printf("%s could not be opened\n", data[i]);
    }
    open_file_from_file_name("data0.txt", NULL);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tasks/task1.c"
#include "tasks/task2.c"
#include "tasks/task3.c"
#include "tasks/task4.c"
#include "tasks/task5.c"
#include "tasks/task6.c"
#include "tasks/task7.c"

#include "trie.c"

void remove_new_line_from_str(char *str){
    char *temp = strchr(str, '\n');
    if(temp != NULL){
        *temp = '\0';
    }
}

void task2(){ 

    char *data[] = {"data0.txt"};
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

int main(){
    task2();
    return 0;
}
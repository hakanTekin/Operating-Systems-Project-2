#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <trie.c>


FILE *open_file_from_file_name(const char *file_name, const char *mode){
    
    FILE *fptr;
    if(mode == NULL){
        fptr = fopen(file_name, "r");
    }else{
        fptr = fopen(file_name, mode);
    }
    return fptr == NULL ? NULL : fptr;
}

bool update_output_file(char *str, int ocurrence){}
char *find_the_correct_line_in_file(char *file_name, char *line_being_searched){
    int pointer_to_line;
}
bool write_new_line_to_file(char *file_name, char *new_line, char *ocurrence){}

bool write_new_number_to_correct_line(char *ptr){}
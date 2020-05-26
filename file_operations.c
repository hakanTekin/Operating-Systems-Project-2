#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *open_file_from_file_name(const char *file_name, const char *mode){
    FILE *fptr;
    if(mode == NULL){
        fptr = fopen(file_name, "r");
    }else{
        fptr = fopen(file_name, mode);
    }
    return fptr == NULL ? NULL : fptr;
}


bool write_new_number_to_correct_line(char *ptr, int new_number){}
char *find_the_correct_line_in_file(FILE *f, char *line_being_searched){}
bool write_new_line_to_file(FILE *f, char *new_line, char *ocurrence){}

//Either inserts the new line, or changes the contents of the existing one
bool update_output_file(char *str, int ocurrence, FILE *f){
    char buffer[9999];
    char dictionary_entry[9999];
    if(f != NULL){
        while(fgets(buffer, sizeof(buffer), f)){
            
            char *Stop = strrchr(buffer, ' ');
            strncpy(dictionary_entry, buffer, Stop - buffer);
            if(strcmp(str, dictionary_entry) == 0){
                write_new_number_to_correct_line(Stop, ocurrence);
            }
        }

        //Could not find the entry. Needs to write new line to the dictionary
        fseek(f,0, SEEK_END);
        char str_ocurrence[9999];
        sprintf(str_ocurrence, "%s %d\n", str, ocurrence);
        fwrite(str_ocurrence, 1, strlen(str_ocurrence), f);

    }
}
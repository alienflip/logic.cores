#include "stdio.h"
#include "stdlib.h"
#include <string.h>

char header_array_input[256];
char header_array_output[256];
char input_array[256];
char output_array[256];
char logic_full[2048];

void compile(){
    char temp[2048];  // Temporary buffer to store the modified string
    int i = 0, j = 0;

    char* find = "))((";
    char* replace = "))|((";

    int find_len = strlen(find);
    int replace_len = strlen(replace);

    while (logic_full[i] != '\0') {
        // If the substring matches the "find" pattern, replace it with "replace"
        if (strncmp(&logic_full[i], find, find_len) == 0) {
            // Copy the replacement into temp
            strcpy(&temp[j], replace);
            j += replace_len;
            i += find_len;  // Move past the found pattern
        } else {
            temp[j++] = logic_full[i++];  // Copy character if no match
        }
    }
    temp[j] = '\0';  // Null-terminate the modified string

    // Copy the modified string back into the original string
    strcpy(logic_full, temp);

    // remove whitespace
    i = 0, j = 0;

    // Loop through the string and copy non-whitespace characters
    while (logic_full[i] != '\0') {
        if (logic_full[i] != ' ' && logic_full[i] != '\t' && logic_full[i] != '\n') {
            logic_full[j++] = logic_full[i];
        }
        i++;
    }
    logic_full[j] = '\0';  // Null-terminate the string after removal
}

void parse_body(char* line, int len, char io_flag, int input_counter){
    char logic_segment_initial[256] = {};
    char logic_segment_final[256] = {};
    char temp[16];
    int segment_counter;
    if(line[len-2] != '1') return;      // find rows with output == 1
    else {                              // parse line and convert to initial boolean expressions
        for(int i = 0; i < len; i++) {
            if(line[i] == ' ' || line[i] == '\n' || line[i] == '|') continue;
            if(line[i]  == '|') io_flag = 'o';
            if(io_flag != 'i') continue;
            char character[2] = {header_array_input[input_counter], '\0'}; 
            if(line[i] == '0') {
                strcat(logic_segment_initial, "~");
                strcat(logic_segment_initial, character);
            }
            if(line[i] == '1'){
                strcat(logic_segment_initial, " ");
                strcat(logic_segment_initial, character);
            }
            input_counter++;
        }
        for (int i = 0; i < 2 * input_counter - 2; i += 2) { // parse boolean exressions into full boolean expressions
            if(i == 0) strcpy(logic_segment_final, "(");
            if (i < 2 * input_counter - 4) {
                snprintf(temp, sizeof(temp), "(%c%c)&", logic_segment_initial[i], logic_segment_initial[i + 1]);
            } else { 
                snprintf(temp, sizeof(temp), "(%c%c))", logic_segment_initial[i], logic_segment_initial[i + 1]);
            }
            strcat(logic_segment_final, temp);
        }
        strcat(logic_full, logic_segment_final);
    }
    printf("BODY:: input:  %s\n", logic_segment_final);
}

void parse_header(char* line, int len, char io_flag, int input_counter, int output_counter){
    for (int i = 0; i < len; i++){
        if(line[i]  == '|')
            io_flag = 'o';
        if(line[i] == ' ' || line[i] == '\n' || line[i] == '|') continue;
        else if(io_flag == 'i') {
            header_array_input[input_counter] = line[i];
            input_counter++;
        }
        else if(io_flag == 'o') {
            header_array_output[output_counter] = line[i];
            output_counter++;
        }  
    }
    printf("META:: count: %d|%d - in|out \n", input_counter, output_counter);
    printf("HEAD:: in|out: %s|%s \n", header_array_input, header_array_output);
}

void parse(char* line, int counter){
    int len = strlen(line); // length of string
    char io_flag = 'i';
    int input_counter = 0;
    int output_counter = 0;
    memset(input_array, 0, sizeof(input_array));  
    memset(output_array, 0, sizeof(output_array));
    if(counter == 0){ // header of table
        parse_header(line, len, io_flag, input_counter, output_counter);
    }
    if(counter > 1){ // body of table
        parse_body(line, len, io_flag, input_counter);
    }
}

int main(int argc, char *argv[]){
    char *file_name = NULL;                 // Declare file_name as a const pointer

    if (argc > 1) {                         // Check if an argument is provided
        file_name = argv[1];                // Assign the argument as filename
    } else {
        printf("No argument provided!\n");
        return 1;
    }

    FILE* file = fopen(file_name, "r");     // Try opening the file
    if (file != NULL) {
        char line[256];
        int counter = 0;
        while (fgets(line, sizeof(line), file)) {
            parse(line, counter);
            counter++;
        }
        compile();
        printf("OUTPUT: %s\n", logic_full);
        fclose(file);
    } else {
        fprintf(stderr, "File cannot be opened: %s\n", file_name);
    }

    return 0;
}

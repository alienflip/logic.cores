#include "stdio.h"

const char AND    = '&';
const char OR     = '|';
const char NOT    = '~';

void join_rows(){}

void parse_row(char* line, int counter){
    // define struct
    printf("%s", line);
    if(counter == 0){
        // input / output names
        // input array/count
        // output array/count
    }
    if(counter > 1){
        // find rows with output == 1
        /// if element == 1, add  element_char to struct
        /// if element == 0, add ~element_char to struct
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
            parse_row(line, counter);
            counter++;
        }
        join_rows();
        fclose(file);
    } else {
        fprintf(stderr, "File cannot be opened: %s\n", file_name);
    }

    return 0;
}

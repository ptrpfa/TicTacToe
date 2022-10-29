#include <stdio.h>
#include <stdlib.h>
#define FILE_PATH "output.txt"
int main() {

    // Initialise file pointer
    FILE * file_ptr = fopen(FILE_PATH, "a");
    // Check if file pointer is valid
    if (file_ptr == NULL){
        printf("%s does not exist!\n", FILE_PATH);
        exit(1);
    }

    fprintf(file_ptr, "%s\n", "testing");
    // Close file pointer
    fclose(file_ptr);

    return 0;

}
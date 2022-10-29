#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main() {

    float temp_array[NO_FEATURES] = {};
    int index;
    float value;

    // Initialise file pointer for reading
    FILE * settings_file = fopen(SETTINGS_FILE, "r");

    // Check if file pointer is valid
    if (settings_file == NULL){
        printf("%s does not exist!\n", SETTINGS_FILE);
        exit(1);
    }
    // Read file contents
    for (int i = 0; i < NO_FEATURES; i++) {
        // Read current line in the file
        fscanf(settings_file, "w%d = %f\n", &index, &value);
        printf("w%d: %f\n", index, value);
        temp_array[index] = value;
    }

    printf("\nArray values:\n");  
    for (int i = 0; i < NO_FEATURES; i++){
        printf("Element %d: %f\n", i, temp_array[i]);
    }
    // Close file pointer
    fclose(settings_file);

    // Open file for writing
    settings_file = fopen(SETTINGS_FILE, "w");

    // Writing to file
    for (int i = 0; i < NO_FEATURES; i++){
        fprintf(settings_file, "w%d = %f\n", i, temp_array[i]);
    }

    // Close file pointer
    fclose(settings_file);
    return 0;

}
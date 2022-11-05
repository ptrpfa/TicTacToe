#include <stdio.h>
#include <time.h>

// Function to delay for a specified amount of seconds
void delay(float seconds){
    // Calculate number of clock cycles to wait for
    clock_t wait = CLOCKS_PER_SEC * seconds;
    // Get total number of clock cycles at the start
    clock_t start = clock();
    // Wait until the stipulated time has passed
    while(clock() < start + wait);
}

int main() {
    delay(0.2);
    printf("after waiting");
    return 0;

}
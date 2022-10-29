#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

    // Initialise random number generator's seed
    srand(time(NULL));

    while(1){
        printf("\nRandom value between 0 to 8: %d", rand() % 9);
    }

    return 0;

}
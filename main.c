#include <stdio.h>
#include <stdlib.h>

#include "forky.h"

int main(int argc, char *argv[]) {
    int num_of_things = atoi(argv[1]);
    int pattern_num = atoi(argv[2]);

    if (num_of_things < 1 || num_of_things > 256) {
        printf("num of things must be between 1 and 256\n");
        return 1;
    }

    if (pattern_num == 1) {
        fprintf(stderr, "Pattern 1\n");
        pattern_1(num_of_things);
    } else if (pattern_num == 2) {
        fprintf(stderr, "Pattern 2\n");
        pattern_2(num_of_things);
    } else {
        printf("pattern must be 1 or 2\n");
        return 1;
    }

    return 0;
}

//Note to self: To capture exact output to results.txt do 
//  ./main <arguments> results.txt 2>&1  

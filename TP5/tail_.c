//
// Created by arnaud on 05/04/23.
//

#include "filesystem.h"

int main(int argc, char** argv){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file_name n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("tail_stupid:\n");
    tail_stupid(argv[1], atoi(argv[2]));
    printf("tail:\n");
    tail(argv[1], atoi(argv[2]));
}
//
// Created by arnaud on 16/05/23.
//

#include "filesystem.h"
int main(int argc, char** argv){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file_name n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    cat(argv[1]);
}

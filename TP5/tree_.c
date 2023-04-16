//
// Created by arnaud on 05/04/23.
//

#include "filesystem.h"
int main(int argc, char** argv){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    tree(argv[1]);
}
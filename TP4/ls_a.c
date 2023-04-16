#include "filesystem.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ls_a(argv[1]);
}

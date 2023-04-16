#include "filesystem.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
      fprintf(stderr, "Usage: %s directory_name pattern\n", argv[0]);
      exit(EXIT_FAILURE);
  }

  int r=find(argv[1], argv[2]);

  if (r==EXIT_FAILURE)
    printf("Pattern %s not found\n", argv[2]);
}

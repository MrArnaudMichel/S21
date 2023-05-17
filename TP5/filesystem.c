//
// Created by arnaud on 05/04/23.
//
#include "filesystem.h"

u_int8_t is_visible(const char *directory) {
    return directory[0] != '.';
}

u_int8_t is_directory(const char *directory) {
    struct stat statbuf;
    stat(directory, &statbuf);
    if (S_ISDIR(statbuf.st_mode)){
        return 1;
    }
    return 0;
}

void print_directory(const char *directory, int order) {
    for (int i = 0; i < order; ++i) {
        printf("|   ");
    }
    printf("|__%s\n", directory);
}

void tree(const char* directory) {
    if (is_directory(directory)) {
        printf("%s\n", directory);
        tree_(directory, 0);
    }
}

void tree_(const char *directory, int order) {
    struct dirent **namelist;
    int n;
    n = scandir(directory, &namelist, 0, 0);
    if (n < 0) {
        return;
    } else {
        for (int i = 0; i < n; i++) {
            if (is_visible(namelist[i]->d_name)) {
                print_directory(namelist[i]->d_name, order);
                if (is_directory(namelist[i]->d_name) == 1) {
                    tree_(namelist[i]->d_name, order + 1);
                }
            }
            free(namelist[i]);
        }
    }
    free(namelist);
}

void head(const char* file, unsigned int n) {
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s\n", file);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    for (int i = 0; i < n; ++i) {
        read = getline(&line, &len, f);
        if (read == -1) {
            break;
        }
        printf("%s", line);
    }
    fclose(f);
    if (line) {
        free(line);
    }
}

void head_(const char* file, unsigned int n) {
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s\n", file);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    for (int i = 0; i < n; ++i) {
        read = getline(&line, &len, f);
        if (read == -1) {
            break;
        }
        printf("%s", line);
    }
    fclose(f);
    if (line) {
        free(line);
    }
}

void tail_stupid(const char* file, unsigned int n) {
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s\n", file);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char** lines = malloc(n * sizeof(char*));
    int i = 0;
    while ((read = getline(&line, &len, f)) != -1) {
        lines[i] = malloc(len * sizeof(char));
        strcpy(lines[i], line);
        i = (i + 1) % n;
    }
    for (int j = 0; j < n; ++j) {
        printf("%s", lines[i]);
        i = (i + 1) % n;
    }
    printf("\n");
    fclose(f);
    if (line) {
        free(line);
    }
    for (int j = 0; j < n; ++j) {
        free(lines[j]);
    }
    free(lines);
}

void tail(const char* file, unsigned int n) {
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s\n", file);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char** lines = malloc(n * sizeof(char*));
    int i = 0;
    while ((read = getline(&line, &len, f)) != -1) {
        lines[i] = malloc(len * sizeof(char));
        strcpy(lines[i], line);
        i = (i + 1) % n;
    }
    for (int j = 0; j < n; ++j) {
        printf("%s", lines[i]);
        i = (i + 1) % n;
    }
    printf("\n");
    fclose(f);
    if (line) {
        free(line);
    }
    for (int j = 0; j < n; ++j) {
        free(lines[j]);
    }
    free(lines);
}

void cat(const char* file){
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s\n", file);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, f)) != -1) {
        printf("%s", line);
    }
    fclose(f);
    if (line) {
        free(line);
    }
}
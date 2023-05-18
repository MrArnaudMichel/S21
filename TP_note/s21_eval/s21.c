#include "s21.h"


uint8_t is_c(char* file_name) {
    if (file_name[strlen(file_name) - 1] == 'c' || file_name[strlen(file_name) - 1] == 'h') {
        return 1;
    }
    return 0;
}

void print_lines(char* file_name, char* expr) {
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        return;
    }
    size_t nb_lines = 0;
    char line[256];
    int first = 1;
    while (fgets(line, sizeof(line), f)) {
        nb_lines++;
        if (strstr(line, expr) != NULL) {
            if (first) {
                printf("%s\n", file_name);
                first = 0;
            }
            printf("%ld: %s", nb_lines, line);
        }
    }
    fclose(f);
}


void ack(char* expr) {
    struct dirent **namelist;
    int n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i) {
        if (is_c(namelist[i]->d_name)) {
            print_lines(namelist[i]->d_name, expr);
            printf("\n");
        }
        free(namelist[i]);
    }
    free(namelist);
}



unsigned long du_file(char *path) {
    struct stat sb;
    if (stat(path, &sb) == -1) {
        return 0;
    }
    printf("%lu\t%s\n", sb.st_blocks * 512 / 1024, path);
    return sb.st_blocks * 512;
}

uint8_t is_file(char *path) {
    struct stat sb;
    if (stat(path, &sb) == -1) {
        return 0;
    }
    return S_ISREG(sb.st_mode);
}

unsigned long du(char *path) {
    struct stat sb;

    if (stat(path, &sb) == -1) {
        return 0;
    } else if (S_ISREG(sb.st_mode)) {
        return du_file(path);
    } else if (S_ISDIR(sb.st_mode)) {
        unsigned long total = 0;
        DIR *dir = opendir(path);
        if (dir == NULL) {
            return 0;
        }
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char *new_path = malloc((strlen(path) + strlen(entry->d_name) + 2) * sizeof(char));
                strcpy(new_path, path);
                strcat(new_path, "/");
                strcat(new_path, entry->d_name);
                total += du(new_path);
                free(new_path);
            }
        }
        closedir(dir);
        return total;
    }
}


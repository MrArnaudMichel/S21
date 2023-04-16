#include "filesystem.h"
#include "dirent.h"
#include "pwd.h"



int ls_a(char* directory) {
    struct dirent **namelist;
    int n;
    n = scandir(directory, &namelist, 0, alphasort);
    if (n < 0){
        return EXIT_FAILURE;}
    else {
        for (int i = 0; i < n; i++) {
            printf("%s \t\t", namelist[i]->d_name);
            free(namelist[i]);
        }
        printf("\n");
    }
    free(namelist);
    return EXIT_SUCCESS;

}

int is_visible(const struct dirent *file) {
    if (file->d_name[0] != '.') {
        return 1;
    }
    return 0;
}

int ls(char* directory) {
    struct dirent **namelist;
    int n;
    n = scandir(directory, &namelist, is_visible, 0);
    if (n < 0){
        return EXIT_FAILURE;}
    else {
        for (int i = 0; i < n; i++) {
            printf("%s \t\t", namelist[i]->d_name);
            free(namelist[i]);
        }
        printf("\n");
    }
    free(namelist);
    return EXIT_SUCCESS;
}

char* get_user(uid_t uid) {
    return getpwuid(uid)->pw_name;
}

char* get_grp(uid_t gid) {
    return getgrgid(gid)->gr_name;
}

unsigned char get_type(unsigned long mode) {
    switch (mode & S_IFMT) {
        case S_IFREG:
            return 'F';
        case S_IFDIR:
            return 'D';
        case S_IFLNK:
            return 'L';
        case S_IFIFO:
            return 'P';
        case S_IFSOCK:
            return 'S';
        case S_IFCHR:
            return 'C';
        case S_IFBLK:
            return 'B';
    }
    return '?';
}

void fmt_rights(mode_t mode, char* rights) {
    strcpy(rights, "---------");
    for (int i = 0; i < 9; i++) {
        if (mode & (1 << (8 - i))) {
            rights[i] = "rwxrwxrwx"[i];
        }
    }
}

void print_line(char mode, char* rights, char* user, char* group, long long size, char* time, char* filename) {
  printf("%c ", mode);
  printf("%s ", rights);
  printf("%10s %10s ", user, group);
  printf("%8lld ", size);
  printf("%s ", time);
  printf("%s\n", filename);
}

int ls_l(char* directory) {
    struct dirent **namelist;
    struct stat sb;
    int n;
    char rights[11];
    char time[20];
    char* user;
    char* group;
    n = scandir(directory, &namelist, is_visible, 0);
    if (n < 0){
        return EXIT_FAILURE;}
    else {
        for (int i = 0; i < n; i++) {
            stat(namelist[i]->d_name, &sb);
            user = get_user(sb.st_uid);
            group = get_grp(sb.st_gid);
            fmt_rights(sb.st_mode, rights);
            strftime(time, 20, "%b %d %H:%M", localtime(&sb.st_mtime));
            print_line(get_type(sb.st_mode), rights, user, group, sb.st_size, time, namelist[i]->d_name);
            free(namelist[i]);
        }
        printf("\n");
    }
    free(namelist);
  return EXIT_SUCCESS;
}

int only_me(const struct dirent *file) {
  return 0;
}

int get_name_from_ino(char* dir, ino_t inode, char* dirname) {
    struct dirent **namelist;
    int n;
    n = scandir(dir, &namelist, 0, 0);
    //printf("%d \n", n);
    if (n < 0){
        return EXIT_FAILURE;}
    else {
        for (int i = 0; i < n; i++) {
            if (namelist[i]->d_ino == inode) {
                strcpy(dirname, namelist[i]->d_name);
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_FAILURE;
}

void pwd() {
    struct dirent **namelist;
    struct stat sb;
    char* dir = ".";
    char* parent = "..";
    char dirname[256] = "\0";
    char path[256];

    strcpy(path, "");
    stat(dir, &sb);
    get_name_from_ino(parent, sb.st_ino, dirname);
    strcat(path, dirname);

    while (sb.st_ino != 2) {
        char current[256];
        chdir(parent);
        stat(dir, &sb);
        get_name_from_ino(parent, sb.st_ino, dirname);
        strcpy(current, dirname);
        strcat(current, "/");
        if (sb.st_ino != 2) {
            strcat(current, path);
            strcpy(path, current);
        }
    }
    char current[256];
    strcpy(current, "/");
    strcat(current, path);
    strcpy(path, current);
    printf("%s \n", path);
}

int find(const char* dir, const char* t) {
    struct dirent **namelist;
    struct stat sb;
    char rights[11];
    char time[20];
    char* user;
    char* group;
    int n;
    n = scandir(dir, &namelist, 0, 0);
    if (n < 0){
        return EXIT_FAILURE;}
    else {
        for (int i = 0; i < n; i++) {
            if (strcmp(namelist[i]->d_name, t) == 0) {
                stat(namelist[i]->d_name, &sb);
                user = get_user(sb.st_uid);
                group = get_grp(sb.st_gid);
                fmt_rights(sb.st_mode, rights);
                strftime(time, 20, "%b %d %H:%M", localtime(&sb.st_mtime));
                print_line(get_type(sb.st_mode), rights, user, group, sb.st_size, time, namelist[i]->d_name);
            }
            if (namelist[i]->d_type == DT_DIR) {
                if (strcmp(namelist[i]->d_name, ".") != 0 && strcmp(namelist[i]->d_name, "..") != 0) {
                    char current[256];
                    strcpy(current, dir);
                    strcat(current, "/");
                    strcat(current, namelist[i]->d_name);
                    find(current, t);
                }
            }
        }
    }
    return EXIT_SUCCESS;
}


int grep(const char* dir, const char* t) {
    struct dirent **namelist;
    struct stat sb;
    int n;
    n = scandir(dir, &namelist, 0, 0);
    if (n < 0){
        return EXIT_FAILURE;}
    else {
        for (int i = 0; i < n; i++) {
            //printf("%s \n", namelist[i]->d_name);
            if (namelist[i]->d_type == DT_REG) {
                FILE* file = fopen(namelist[i]->d_name, "r");
                char line[256];
                while (fgets(line, sizeof(line), file)) {
                    if (strstr(line, t) != NULL) {
                        printf("%s: %s", namelist[i]->d_name, line);
                    }
                }
                fclose(file);
            }
        }
    }
    return EXIT_FAILURE;
}

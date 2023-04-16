//
// Created by arnaud on 05/04/23.
//

#ifndef S21_FILESYSTEM_H
#define S21_FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

u_int8_t is_visible(const char *directory);
u_int8_t is_directory(const char *directory);
void print_directory(const char *directory, int order);
void tree(const char* directory);
void tree_(const char *directory, int order);
void head(const char* file, unsigned int n);
void tail_stupid(const char* file, unsigned int n);
void tail(const char* file, unsigned int n);


#endif //S21_FILESYSTEM_H

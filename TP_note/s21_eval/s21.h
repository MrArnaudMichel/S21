#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statvfs.h>

#define MAX_LINE_LENGTH 1024

uint8_t is_c(char* file_name);
void print_lines(char* file_name, char* expr);
void ack(char* expr);

unsigned long du_file(char *path);
unsigned long du(char *path);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void copy_file(char *src, char *dst, int recursive);
void copy_directory_recursively(const char *src, const char *dst);
int is_directory(const char *path);
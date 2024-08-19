#ifndef FUNC_H
#define FUNC_H


#include <ncurses.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILES 1024

typedef struct {
    char *name;
    int is_dir;
} File;

int compare_files(const void *a, const void *b);

void list_files(const char *path, File *files, int *count);

void draw_panel(WINDOW *win, File *files, int count, int highlight);

void change_directory(const char *path, File *files, int *count);
#endif

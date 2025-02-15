#ifndef FUNC_H
#define FUNC_H

#include <ncurses.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "RBTree.h"

#define MAX_FILES 1024

typedef struct {
    char* name;
    int is_dir;
} File;

void list_files(const char* path, RBTree* tree);
void draw_panel(WINDOW* win, RBTree* tree, int highlight);
void change_directory(const char* path, RBTree* tree);

#endif

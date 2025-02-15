#include "lab9_2.h"
#include "RBTree.h"
#include <stdio.h> 
#include <sys/stat.h> 

void list_files(const char* path, RBTree* tree) {
    DIR* dir;
    struct dirent* entry;
    struct stat statbuf;
    char fullpath[1024];

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        if (stat(fullpath, &statbuf) == -1) {
            perror("stat");
            continue;
        }
        rb_insert(tree, entry->d_name, S_ISDIR(statbuf.st_mode));
    }

    closedir(dir);
}

void draw_panel(WINDOW* win, RBTree* tree, int highlight) {
    werase(win);
    box(win, 0, 0);

    int i = 0;
    RBNode* node = rb_get_index(tree, 0);
    while (node && node != tree->nil) {
        if (i == highlight) {
            wattron(win, A_REVERSE);
        }
        if (node->name == NULL) {
            mvwprintw(win, i + 1, 1, "(null)");
        }
        else {
            if (strcmp(node->name, "..") == 0) {
                mvwprintw(win, i + 1, 1, "/..");
            }
            else if (node->is_dir) {
                mvwprintw(win, i + 1, 1, "%s/", node->name);
            }
            else {
                mvwprintw(win, i + 1, 1, "%s", node->name);
            }
        }
        if (i == highlight) {
            wattroff(win, A_REVERSE);
        }
        i++;
        node = rb_get_index(tree, i);
    }

    wrefresh(win);
}

void change_directory(const char* path, RBTree* tree) {
    if (chdir(path) == 0) {
        rb_clear(tree);
        list_files(".", tree);
    }
    else {
        perror("chdir");
    }
}
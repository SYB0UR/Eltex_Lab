#include "lab9_2.h"



int compare_files(const void *a, const void *b) {
    File *fileA = (File *)a;
    File *fileB = (File *)b;
    if (fileA->is_dir != fileB->is_dir) {
        return fileB->is_dir - fileA->is_dir;
    }
    return strcmp(fileA->name, fileB->name);
}

void list_files(const char *path, File *files, int *count) {
    DIR *dir;
    struct dirent *entry;
    *count = 0;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL && *count < MAX_FILES) {
        files[*count].name = strdup(entry->d_name);
        files[*count].is_dir = (entry->d_type == DT_DIR);
        (*count)++;
    }

    closedir(dir);

    qsort(files, *count, sizeof(File), compare_files);
}

void draw_panel(WINDOW *win, File *files, int count, int highlight) {
    werase(win);
    box(win, 0, 0);

    for (int i = 0; i < count; i++) {
        if (i == highlight) {
            wattron(win, A_REVERSE);
        }
        if (strcmp(files[i].name, "..") == 0) {
            mvwprintw(win, i + 1, 1, "/..");
        } else if (files[i].is_dir) {
            mvwprintw(win, i + 1, 1, "%s/", files[i].name);
        } else {
            mvwprintw(win, i + 1, 1, "%s", files[i].name);
        }
        if (i == highlight) {
            wattroff(win, A_REVERSE);
        }
    }

    wrefresh(win);
}

void change_directory(const char *path, File *files, int *count) {
    if (chdir(path) == 0) {
        list_files(".", files, count);
    } else {
        perror("chdir");
    }
}

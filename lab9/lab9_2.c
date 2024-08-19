#include "lab9_2.h"

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);

    WINDOW *left_panel = newwin(height, width / 2, 0, 0);
    WINDOW *right_panel = newwin(height, width / 2, 0, width / 2);

    int active_panel = 0; 
    int left_highlight = 0, right_highlight = 0;
    File left_files[MAX_FILES], right_files[MAX_FILES];
    int left_count = 0, right_count = 0;

    list_files(".", left_files, &left_count);
    list_files(".", right_files, &right_count);

    while (1) {
        draw_panel(left_panel, left_files, left_count, left_highlight);
        draw_panel(right_panel, right_files, right_count, right_highlight);

        int ch = getch();
        if (ch == '\t') {
            active_panel = !active_panel;
        } else if (ch == 'q') {
            break;
        } else if (ch == KEY_UP) {
            if (active_panel == 0 && left_highlight > 0) {
                left_highlight--;
            } else if (active_panel == 1 && right_highlight > 0) {
                right_highlight--;
            }
        } else if (ch == KEY_DOWN) {
            if (active_panel == 0 && left_highlight < left_count - 1) {
                left_highlight++;
            } else if (active_panel == 1 && right_highlight < right_count - 1) {
                right_highlight++;
            }
        } else if (ch == '\n') { 
            if (active_panel == 0 && left_files[left_highlight].is_dir) {
                change_directory(left_files[left_highlight].name, left_files, &left_count);
                left_highlight = 0;
            } else if (active_panel == 1 && right_files[right_highlight].is_dir) {
                change_directory(right_files[right_highlight].name, right_files, &right_count);
                right_highlight = 0;
            }
        }
    }

    for (int i = 0; i < left_count; i++) {
        free(left_files[i].name);
    }
    for (int i = 0; i < right_count; i++) {
        free(right_files[i].name);
    }

    delwin(left_panel);
    delwin(right_panel);
    endwin();

    return 0;
}

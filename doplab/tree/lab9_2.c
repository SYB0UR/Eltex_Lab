#include "lab9_2.h"
#include "RBTree.h"
#include <stdio.h>

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);

    WINDOW* left_panel = newwin(height, width / 2, 0, 0);
    WINDOW* right_panel = newwin(height, width / 2, 0, width / 2);

    int active_panel = 0;
    int left_highlight = 0, right_highlight = 0;
    RBTree* left_tree = rb_create();
    RBTree* right_tree = rb_create();

    if (left_tree == NULL || right_tree == NULL) {
        fprintf(stderr, "Failed to create RBTree\n");
        return 1;
    }

    list_files(".", left_tree);
    list_files(".", right_tree);

    while (1) {
        draw_panel(left_panel, left_tree, left_highlight);
        draw_panel(right_panel, right_tree, right_highlight);

        int ch = getch();
        if (ch == '\t') {
            active_panel = !active_panel;
        }
        else if (ch == 'q') {
            break;
        }
        else if (ch == KEY_UP) {
            if (active_panel == 0 && left_highlight > 0) {
                left_highlight--;
            }
            else if (active_panel == 1 && right_highlight > 0) {
                right_highlight--;
            }
        }
        else if (ch == KEY_DOWN) {
            if (active_panel == 0 && left_highlight < rb_size(left_tree) - 1) {
                left_highlight++;
            }
            else if (active_panel == 1 && right_highlight < rb_size(right_tree) - 1) {
                right_highlight++;
            }
        }
        else if (ch == '\n') {
            if (active_panel == 0) {
                RBNode* file = rb_get_index(left_tree, left_highlight);
                if (file->is_dir) {
                    change_directory(file->name, left_tree);
                    left_highlight = 0;
                }
            }
            else if (active_panel == 1) {
                RBNode* file = rb_get_index(right_tree, right_highlight);
                if (file->is_dir) {
                    change_directory(file->name, right_tree);
                    right_highlight = 0;
                }
            }
        }
    }

    rb_destroy(left_tree);
    rb_destroy(right_tree);
    delwin(left_panel);
    delwin(right_panel);
    endwin();

    return 0;
}
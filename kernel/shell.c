#include "shell.h"
#include "terminal.h"
#include "keyboard.h"

int strcmp(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i])
            return 0;
        i++;
    }
    return a[i] == b[i];
}

void shell_run() {
    char command[100];
    int index = 0;
    terminal_write("MiniOS > ");
    while (1) {

    char c = keyboard_getchar();

    if (c == '\b') {

        if (index > 0) {
            index--;
            terminal_backspace();
        }

    } else {

        terminal_putchar(c);

        if (c == '\n') {

            command[index] = '\0';

            if (strcmp(command, "help")) {
                terminal_write("Commands: help clear about\n");

            } else if (strcmp(command, "about")) {
                terminal_write("MiniOS by Shubham\n");

            } else if (strcmp(command, "clear")) {
                terminal_clear();

            } else {
                terminal_write("Unknown command\n");
            }

            index = 0;
            terminal_write("MiniOS > ");

        } else {

            command[index++] = c;
        }
    }
}


}
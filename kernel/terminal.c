#include "terminal.h"

static int row = 0;
static int col = 0;

static char* video_memory = (char*) 0xB8000;

void terminal_clear() {
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07;
    }

    row = 0;
    col = 0;
}

void terminal_putchar(char c) {

    if (c == '\n') {
        row++;
        col = 0;
        return;
    }

    int index = (row * 80 + col) * 2;

    video_memory[index] = c;
    video_memory[index + 1] = 0x07;

    col++;

    if (col >= 80) {
        col = 0;
        row++;
    }
}

void terminal_write(const char* str) {
    int i = 0;

    while (str[i] != '\0') {
        terminal_putchar(str[i]);
        i++;
    }
}

void terminal_backspace() {

    if (col > 0) {

        col--;

        int index = (row * 80 + col) * 2;

        video_memory[index] = ' ';
        video_memory[index + 1] = 0x07;
    }
}

void terminal_print_number(int n)
{
    terminal_putchar('0' + (n / 10));
    terminal_putchar('0' + (n % 10));
}
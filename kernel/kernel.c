#include "terminal.h"
#include "shell.h"

void kernel_main() {

    terminal_clear();

    terminal_write("Welcome to ShubOS\n");

    terminal_write("Kernel Loaded Successfully\n");
    shell_run();

    while (1);
}
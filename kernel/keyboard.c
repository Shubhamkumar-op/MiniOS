#include "keyboard.h"

unsigned char keyboard_map[128] = {
    0, 27, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y',
    'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h',
    'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b',
    'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile (
        "inb %1, %0"
        : "=a"(result)
        : "Nd"(port)
    );
    return result;
}

// char keyboard_getchar() {

//     unsigned char scancode;

//     while (1) {

//         scancode = inb(0x60);

//         if (scancode > 0 && scancode < 128) {

//             char c = keyboard_map[scancode];

//             while (inb(0x60) != (scancode + 128));

//             if (c)
//                 return c;
//         }
//     }
// }

char keyboard_getchar() {

    while (1) {
        if (!(inb(0x64) & 1))
            continue;

        unsigned char scancode = inb(0x60);
        if (scancode & 0x80)
            continue;

        char c = keyboard_map[scancode];

        if (c)
            return c;
    }
}
#include <main.h>

int _putchar(char c) {
    return write(fileno(stdout), &c, 1);
}

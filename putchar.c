#include <main.h>
#include <unistd.h>  // for write(), fileno()

int _putchar(char c) {
    return write(fileno(stdout), &c, 1);
}

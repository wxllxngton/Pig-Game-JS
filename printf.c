// Online C compiler to run C program online
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

int _printf(const char *format, ...) {
    va_list arglist;
    int charcount = 0;

    va_start(arglist, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == '%') {
                putchar('%');
                charcount++;
            }
            else if (*format == 'c') {
                char c = va_arg(arglist, int);
                putchar(c);
                charcount++;
            }
            else if (*format == 's') {
                char *s = va_arg(arglist, char*);
                fputs(s, stdout);
                charcount += strlen(s);
            }
            else if (*format == 'd' || *format == 'i') {
                int num = va_arg(arglist, int);
                if (num < 0) {
                    putchar('-');
                    charcount++;
                    num = -num;
                }
                if (num == 0) {
                    putchar('0');
                    charcount++;
                }
                else {
                    int num_digits = 0;
                    int tmp_num = num;
                    while (tmp_num > 0) {
                        num_digits++;
                        tmp_num /= 10;
                    }
                    char num_str[num_digits];
                    for (int i = num_digits - 1; i >= 0; i--) {
                        num_str[i] = '0' + (num % 10);
                        num /= 10;
                    }
                    for (int i = 0; i < num_digits; i++) {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
            else if (*format == 'x' || *format == 'X') {
                unsigned int num = va_arg(arglist, unsigned int);
                if (num == 0) {
                    putchar('0');
                    charcount++;
                }
                else {
                    char num_str[20];
                    int index = 0;
                    while (num > 0) {
                        int digit = num % 16;
                        if (digit < 10) {
                            num_str[index++] = '0' + digit;
                        }
                        else {
                            if (*format == 'x') {
                                num_str[index++] = 'a' + digit - 10;
                            }
                            else {
                                num_str[index++] = 'A' + digit - 10;
                            }
                        }
                        num /= 16;
                    }
                    for (int i = index - 1; i >= 0; i--) {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
            else if (*format == 'o') {
                unsigned int num = va_arg(arglist, unsigned int);
                if (num == 0) {
                    putchar('0');
                    charcount++;
                }
                else {
                    int num_digits = 0;
                    unsigned int tmp_num = num;
                    while (tmp_num > 0) {
                        num_digits++;
                        tmp_num /= 8;
                    }
                    char num_str[num_digits];
                    for (int i = num_digits - 1; i >= 0; i--) {
                        num_str[i] = '0' + (num % 8);
                        num /= 8;
                    }
                    for (int i = 0; i < num_digits; i++) {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
            else if (*format == 'p') {
                void *ptr = va_arg(arglist, void *);
                unsigned long int ui = (unsigned long int)ptr;
                putchar('0');
                putchar('x');
                int num_digits = 0;
                unsigned long int tmp_num = ui;
                while (tmp_num > 0) {
                    num_digits++;
                    tmp_num /= 16;
                }
                char hex_str[num_digits];
                for (int i = num_digits - 1; i >= 0; i--) {
                    int rem = ui % 16;
                    if (rem < 10) {
                        hex_str[i] = rem + '0';
                    } else {
                        hex_str[i] = rem - 10 + 'a';
                    }
                    ui /= 16;
                }
                for (int i = 0; i < num_digits; i++) {
                    putchar(hex_str[i]);
                    charcount++;
                }
            }
            else if (*format == 'u') {
                unsigned int num = va_arg(arglist, unsigned int);
                if (num == 0) {
                    putchar('0');
                    charcount++;
                }
                else {
                    int num_digits = 0;
                    unsigned int tmp_num = num;
                    while (tmp_num > 0) {
                        num_digits++;
                        tmp_num /= 10;
                    }
                    char num_str[num_digits];
                    for (int i = num_digits - 1; i >= 0; i--) {
                        num_str[i] = '0' + (num % 10);
                        num /= 10;
                    }
                    for (int i = 0; i < num_digits; i++) {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
        }
        else {
            putchar(*format);
            charcount++;
        }
        format++;
    }

    va_end(arglist);
    return charcount;
}



int main(void)
{
    int len;
    int len2;
    unsigned int ui;
    void *addr;

    len = _printf("Let's try to printf a simple sentence.\n");
    len2 = printf("Let's try to printf a simple sentence.\n");
    ui = (unsigned int)INT_MAX + 1024;
    addr = (void *)0x7ffe637541f0;
    _printf("Length:[%d, %i]\n", len, len);
    printf("Length:[%d, %i]\n", len2, len2);
    _printf("Negative:[%d]\n", -762534);
    printf("Negative:[%d]\n", -762534);
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    _printf("Unsigned octal:[%o]\n", ui);
    printf("Unsigned octal:[%o]\n", ui);
    _printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    _printf("Character:[%c]\n", 'H');
    printf("Character:[%c]\n", 'H');
    _printf("String:[%s]\n", "I am a string !");
    printf("String:[%s]\n", "I am a string !");
    _printf("Address:[%p]\n", addr);
    printf("Address:[%p]\n", addr);
    len = _printf("Percent:[%%]\n");
    len2 = printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    printf("Len:[%d]\n", len2);
    _printf("Unknown:[%r]\n");
    printf("Unknown:[%r]\n");
    return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

int _printf(const char *format, ...) 
{
    va_list arglist;
    int charcount = 0;

    va_start(arglist, format);

    while (*format != '\0') 
    {
        if (*format == '%') 
        {
            format++;
            if (*format == '%') 
            {
                putchar('%');
                charcount++;
            }
            else if (*format == 'c') 
            {
                char c = va_arg(arglist, int);
                putchar(c);
                charcount++;
            }
            else if (*format == 's') 
            {
                char *s = va_arg(arglist, char*);
                fputs(s, stdout);
                charcount += strlen(s);
            }
            else if (*format == 'd' || *format == 'i') 
            {
                int num = va_arg(arglist, int);
                if (num < 0) 
                {
                    putchar('-');
                    charcount++;
                    num = -num;
                }
                if (num == 0) 
                {
                    putchar('0');
                    charcount++;
                }
                else 
                {
                    int num_digits = 0, i;
                    int tmp_num = num;
                    char *num_str;
                    while (tmp_num > 0) 
                    {
                        num_digits++;
                        tmp_num /= 10;
                    }
                    num_str = malloc(sizeof(char) * num_digits);
                    i = num_digits - 1;
                    for (; i >= 0; i--) 
                    {
                        num_str[i] = '0' + (num % 10);
                        num /= 10;
                    }
                    i = 0;
                    for (; i < num_digits; i++) 
                    {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
            else if (*format == 'x' || *format == 'X') 
            {
                unsigned int num = va_arg(arglist, unsigned int);
                if (num == 0) 
                {
                    putchar('0');
                    charcount++;
                }
                else 
                {
                    char num_str[20];
                    int index = 0, i;
                    while (num > 0) 
                    {
                        int digit = num % 16;
                        if (digit < 10) 
                        {
                            num_str[index++] = '0' + digit;
                        }
                        else 
                        {
                            if (*format == 'x') 
                            {
                                num_str[index++] = 'a' + digit - 10;
                            }
                            else 
                            {
                                num_str[index++] = 'A' + digit - 10;
                            }
                        }
                        num /= 16;
                    }
                    i = index - 1;
                    for (; i >= 0; i--) 
                    {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
            else if (*format == 'o') 
            {
                unsigned int num = va_arg(arglist, unsigned int);
                if (num == 0) 
                {
                    putchar('0');
                    charcount++;
                }
                else 
                {
                    int num_digits = 0, i;
                    unsigned int tmp_num = num;
                    char *num_str;
                    while (tmp_num > 0) 
                    {
                        num_digits++;
                        tmp_num /= 8;
                    }
                    num_str = malloc(sizeof(char) * num_digits);
                    i = num_digits - 1;
                    for (; i >= 0; i--) 
                    {
                        num_str[i] = '0' + (num % 8);
                        num /= 8;
                    }
                    i = 0;
                    for (; i < num_digits; i++) 
                    {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
            else if (*format == 'p') 
            {
                void *ptr = va_arg(arglist, void *);
                int num_digits = 0, i;
                char *hex_str;
                unsigned long int ui = (unsigned long int)ptr;
                unsigned long int tmp_num = ui;
                putchar('0');
                putchar('x');
                while (tmp_num > 0) 
                {
                    num_digits++;
                    tmp_num /= 16;
                }
                hex_str = malloc(sizeof(char) * num_digits);
                i = num_digits - 1;
                for (; i >= 0; i--) 
                {
                    int rem = ui % 16;
                    if (rem < 10) 
                    {
                        hex_str[i] = rem + '0';
                    } else 
                    {
                        hex_str[i] = rem - 10 + 'a';
                    }
                    ui /= 16;
                }
                i = 0;
                for (; i < num_digits; i++) 
                {
                    putchar(hex_str[i]);
                    charcount++;
                }
            }
            else if (*format == 'u') 
            {
                unsigned int num = va_arg(arglist, unsigned int);
                if (num == 0) 
                {
                    putchar('0');
                    charcount++;
                }
                else {
                    int num_digits = 0, i;
                    unsigned int tmp_num = num;
                    char *num_str;
                    while (tmp_num > 0) 
                    {
                        num_digits++;
                        tmp_num /= 10;
                    }
                    num_str = malloc(sizeof(char) * num_digits);
                    i = num_digits - 1;
                    for (; i >= 0; i--) 
                    {
                        num_str[i] = '0' + (num % 10);
                        num /= 10;
                    }
                    i = 0;
                    for (; i < num_digits; i++) 
                    {
                        putchar(num_str[i]);
                        charcount++;
                    }
                }
            }
            else 
            {
                putchar('%');
                putchar(*format);
                charcount += 2;
            }
        }
        else 
        {
            putchar(*format);
            charcount++;
        }
        format++;
    }

    va_end(arglist);
    return charcount;
}


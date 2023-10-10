#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// Function to convert an integer to a string
int From_int_to_String(char *BUFFER, int value)
{
    int count = 0;
    int isNegative = 0;

    // Handle negative valuebers
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    // Convert each diGIT to a character in reverse order
    do {
        BUFFER[count++] = value % 10 + '0';
        value /= 10;
    } while (value != 0);

    // Add the negative sign if necessary
    if (isNegative)
        BUFFER[count++] = '-';

    // Reverse the string
    for (int i = 0, j = count - 1; i < j; i++, j--) {
        char temp = BUFFER[i];
        BUFFER[i] = BUFFER[j];
        BUFFER[j] = temp;
    }

    return count;
}

int my_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int count = 0;  // Keep track of the valueber of characters written

    for (const char *c = format; *c != '\0'; c++)
    {
        if (*c != '%')
        {
            // Ordinary character, write it to stdout
            write(STDOUT_FILENO, c, 1);
            count++;
            continue;
        }

        // Move past the '%'
        c++;

        // Handle the conversion specifier
        switch (*c)
        {
            case 'd':
            {
                int value = va_arg(args, int);
                // Convert the integer to a string and write it to stdout
                char BUFFER[20];  // Assuming a maximum of 20 diGITs
                int len = From_int_to_String(BUFFER, value);
                write(STDOUT_FILENO, BUFFER, len);
                count += len;
                break;
            }
            case 'o':
            {
                unsigned int value = va_arg(args, unsigned int);
                // Convert the unsigned integer to an octal string and write it to stdout
                char BUFFER[20];  // Assuming a maximum of 20 diGITs
                int index = 0;
                do {
                    BUFFER[index++] = (value % 8) + '0';
                    value /= 8;
                } while (value != 0);
                for (int j = index - 1; j >= 0; j--) {
                    write(STDOUT_FILENO, &BUFFER[j], 1);
                    count++;
                }
                break;
            }
            case 'u':
            {
                unsigned int value = va_arg(args, unsigned int);
                // Convert the unsigned integer to a decimal string and write it to stdout
                char BUFFER[20];  // Assuming a maximum of 20 diGITs
                int len = From_int_to_String(BUFFER, value);
                write(STDOUT_FILENO, BUFFER, len);
                count += len;
                break;
            }
            case 'x':
            {
                unsigned int value = va_arg(args, unsigned int);
                // Convert the unsigned integer to a lowercase hexadecimal string and write it to stdout
                char BUFFER[20];  // Assuming a maximum of 20 diGITs
                int index = 0;
                do {
                    int diGIT = value % 16;
                    if (diGIT < 10)
                        BUFFER[index++] = diGIT + '0';
                    else
                        BUFFER[index++] = diGIT - 10 + 'a';
                    value /= 16;
                } while (value != 0);
                for (int j = index - 1; j >= 0; j--) {
                    // Convert the lowercase letter to uppercase
                    char uppercase = BUFFER[j];
                    if (uppercase >= 'a' && uppercase <= 'f')
                        uppercase -= 32;  // Convert lowercase letter to uppercase
                    write(STDOUT_FILENO, &uppercase, 1);
                    count++;
                }
                break;
            }
            case 'c':
            {
                int ch = va_arg(args, int);
                // Write the character to stdout
                write(STDOUT_FILENO, &ch, 1);
                count++;
                break;
            }
            case 's':
            {
                char *str = va_arg(args, char *);
                if (str == NULL) {
                    // Handling the NULL string
                    const char *nullStr = "(null)";
                    write(STDOUT_FILENO, nullStr, strlen(nullStr));
                    count += strlen(nullStr);
                } else {
                    // Write the string to stdout
                    int len = strlen(str);
                    write(STDOUT_FILENO, str, len);
                    count += len;
                }
                break;
            }
            case 'p':
            {
                void *ptr = va_arg(args, void *);
                // Convert the pointer to a hexadecimal string and write it to stdout
                char BUFFER[20];  // Assuming a maximum of 20 diGITs
                unsigned long long value = (unsigned long long)ptr;
                int index = 0;
                do {
                    int diGIT = value % 16;
                    if (diGIT < 10)
                        BUFFER[index++] = diGIT + '0';
                    else
                        BUFFER[index++] = diGIT - 10 + 'a';
                    value /= 16;
                } while (value != 0);
                // Add '0x' prefix before the hexadecimal valueber
                write(STDOUT_FILENO, "0x", 2);
                count += 2;
                for (int j = index - 1; j >= 0; j--) {
                    write(STDOUT_FILENO, &BUFFER[j], 1);
                    count++;
                }
                break;
            }
            default:
                // Invalid conversion specifier, ignore it
                write(STDOUT_FILENO, "%", 1);  // Write '%'
                write(STDOUT_FILENO, c, 1);  // Write the invalid specifier
                count += 2;
                break;
        }
    }

    va_end(args);

    return count;
}


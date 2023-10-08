#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 1000

void print_ngram(char *string)
{
    int counts[256] = {0};
    int i, len;

    len = strlen(string);

    for (i = 0; i < len; i++) {
        counts[(int)string[i]]++;
    }

    for (i = 0; i < 256; i++) {
        if (counts[i] > 0) {
            printf("%c:%d\n", i, counts[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++) {
        print_ngram(argv[i]);
    }

    return 0;
}
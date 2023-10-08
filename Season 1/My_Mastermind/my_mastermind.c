#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


// Organizing all the functions names first to improve readability.
int countIncorrectCode(char* unknown_value, char* Trial);
int countWellPlaced(char* unknown_value, char* TrIal);
int confirmedEntry(char* trying);
int OutputGuessEntry(char input[]);

int main(int argc, char** argv) {
    int MaxLen = 5;
    int guess_length = 6;
    int round_count = 0;
    char unknown_value[MaxLen];
    char guess[guess_length];

    // Generate secret code or accept user-provided code
    if (argc > 1 && strcmp(argv[1], "-c") == 0) {
        int digit_count = 4;
        for (int i = 0; i < digit_count; i++) 
        {
            unknown_value[i] = argv[2][i];
        }
    } else {
        srand(time(NULL));
        int used_digits[MaxLen];
        int random_number;
        int digit_count = 4;
        bool unique_digit;
        for (int i = 0; i < digit_count; i++) 
        {
            do {
                unique_digit = true;
                random_number = (rand() % 8);
                for (int u = 0; u < i; u++) 
                {
                    if (used_digits[u] == random_number) 
                    {
                        unique_digit = false;
                        break;
                    }
                }
            } while (!unique_digit);
            unknown_value[i] = (random_number + '0');
            used_digits[i] = random_number;
        }
    }

    unknown_value[4] = '\0';

    // Requesting for secret codes from the user
    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (countWellPlaced(unknown_value, guess) < 4 && round_count < 10) {
        if (OutputGuessEntry(guess) == 0) 
        {
            
            return 0;
        }

        if (confirmedEntry(guess)) 
        {
            printf("\nRound %d\nWell placed pieces: %d\nMisplaced pieces: %d\n", 
            
            round_count, countWellPlaced(unknown_value, guess), countIncorrectCode(unknown_value, guess) - countWellPlaced(unknown_value, guess));
            
            round_count++;
        } else {
            printf("Wrong input!\n");
        }
    }

    printf("Congratz! You did it!");

    return 0;
}

int countIncorrectCode(char* unknown_value, char* Trial) {
    int invalid_code = 0;
    int x, y;
    int trial_length = strlen(Trial);
    int unknown_value_length = strlen(unknown_value);

    for (x = 0; x < trial_length; x++) {
        for (y = 0; y < unknown_value_length; y++) {
            if (Trial[x] == unknown_value[y]) {
                invalid_code++;
                break;
            }
        }
    }

    return invalid_code;
}

int countWellPlaced(char* unknown_value, char* TrIal) {
    int COUNTER_placed = 0;
    int a;
    int guess_length = strlen(TrIal);

    for (a = 0; a < guess_length; a++) {
        if (TrIal[a] == unknown_value[a]) {
            COUNTER_placed++;
        }
    }

    return COUNTER_placed;
}


// Let's check to confirm the entries from the user
int confirmedEntry(char* trying) {
    int CounTER = 0;

    for (int i = 0; trying[i] != '\0'; i++) {
        char MaxLen = '8';

        if (trying[i] >= '0' && trying[i] <= MaxLen) {
            CounTER++;
        }
    }

    return CounTER == 4 ? 1 : 0;
}


int OutputGuessEntry(char input[]) {
    int MaxLen = 5;
    int user_input = read(0, input, MaxLen);
    input[MaxLen] = '\0';
    return user_input;
}

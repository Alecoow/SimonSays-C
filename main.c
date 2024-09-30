#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "main.h"

int main(void) {
    HANDLE cstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(cstdout, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode(cstdout, mode);
    setbuf(stdout, NULL);

    srand(time(NULL));
    int dimensions = 1;
    int score = 0;
    int level = 1;
    ClearConsole(score);

    for (int difficulty = 1; difficulty < 6; difficulty++) {
        if (!(difficulty % 5)) {
            dimensions++; // every fifth level increases the dimensions of the game, while resetting the "difficulty". Final product could have user memorize grid then pick certain numbers from it, using power-ups if it's too difficult
            difficulty = 1;
        }

        int** simon_numbers = AllocateArray(dimensions, difficulty);
        PopulateList(dimensions, difficulty, simon_numbers);


        for (int i = 0; i < dimensions; i++) {
            for (int j = 0; j < difficulty; j++) {
                printf("%i  ", simon_numbers[i][j]);
                Sleep(500);
            }
            Sleep(2000);
            ClearConsole(score);
            printf("\n");
        }
        int flattened_array[dimensions*difficulty];
        FlattenArray(simon_numbers, dimensions, difficulty, flattened_array);
        FreeArray(simon_numbers, dimensions, difficulty);

        Sleep(1500);
        ClearConsole(score);
        Sleep(1000);

        printf("Enter the sequence, separated by commas:\n");

        char buffer[100];
        memset(buffer, 0, 100);
        fgets(buffer, 100, stdin);
        int result = CompareAnswer(buffer, flattened_array, dimensions * difficulty);
        if (result == 1) {
            printf("Good job! Moving to level %i\n", ++level);
            Sleep(2500);
            ClearConsole(score);
        } else if (result == 0) {
            printf("Incorrect! You made it to level %i\n", level);
            Sleep(5000);
            return 1;
        } else {
            printf("Invalid character(s)! You made it to level %i\n", level);
            Sleep(5000);
            return 1;
        }
        score++;
    }
    return 0;
}
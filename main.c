#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#include "main.h"

enum POWERUPS { //TODO: implement
    POWERUP_REVEAL = 1, // activate to reveal the correct answer
    POWERUP_RESHUFFLE = 1 << 1, // activate to replay the same level but with different numbers
    POWERUP_DOUBLE_POINTS = 1 << 2, // activate to either twice the score if correct, or reset the score to 0
};

int main(void) {
    HANDLE cstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(cstdout, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode(cstdout, mode);

    srand(time(NULL));
    int dimensions = 1;
    int score = 0;
    int level = 1;
    for (int difficulty = 1; difficulty < 6; difficulty++) {
        if (!(difficulty % 5)) {
            dimensions++; // every fifth level increases the dimensions of the game, while resetting the "difficulty". Final product could have user memorize grid then pick certain numbers from it, using power-ups if it's too difficult
            difficulty = 1;
        }

        char** simon_numbers = malloc(dimensions * sizeof(char*));
        for (int i = 0; i < dimensions; i ++) {
            simon_numbers[i] = malloc(difficulty * sizeof(int));
        }
        PopulateList(dimensions, difficulty, simon_numbers);

        char score_buffer[24];
        sprintf_s(score_buffer, sizeof(score_buffer), "Score: %d", score);
        int score_offset = strlen(score_buffer);
        printf("\x1b[0;%iH", 120-score_offset);
        printf("%s\n", score_buffer);
        printf("\x1b[0;80H");
        printf("PowerUps: ");
        printf("\x1b[H");

        for (int i = 0; i < dimensions; i++) {
            for (int j = 0; j < difficulty; j++) {
                setbuf(stdout, NULL);
                printf("%d\n", simon_numbers[i][j]);
            }
        }
        char flattened_array[dimensions*difficulty];
        FlattenArray(simon_numbers, dimensions, difficulty, flattened_array);
        free(simon_numbers);

        Sleep(1500);
        ClearConsole(score);
        Sleep(1000);

        printf("Enter the sequence, separated by commas:\n");

        char buffer[100];
        memset(buffer, 0, 100);
        fgets(buffer, 100, stdin);
        if (CompareAnswer(buffer, flattened_array, dimensions*difficulty)) {
            printf("Good job! Moving to level %d\n", level++);
            Sleep(2500);
            ClearConsole(score);
        } else {
            printf("Incorrect! You made it to level %d\n", level);
            Sleep(5000);
            return 1;
        }
        score++;
    }
    return 0;
}
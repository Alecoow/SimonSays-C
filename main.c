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
    int score_multiplier = 1;
    float time_multiplier = 1.0f;
    bool extra_life = false;
    ClearConsole(score, level);
    int event = 0;
    bool event_active = false;
    // Game ends


    printf("Welcome to Simon Says! How far can you get in 5 minutes?");

    Sleep(2500);
    ClearConsole(score, level);
    clock_t start_time = clock();

    for (int difficulty = 1; difficulty < 6; difficulty++) {
        double time_elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        if (time_elapsed >= 300.0) {
            printf("Time's up!\n");
            break;
        }

        if (!(difficulty % 5)) {
            dimensions++; // every fifth level increases the dimensions of the game, while resetting the "difficulty".
            difficulty = 1;
        }

        if (event_active) {
            printf("Event Started: ");
            switch(event) {
            case DOUBLE_OR_NOTHING: // DOUBLE_OR_NOTHING
                printf("Double or Nothing\n");
                break;
            case EXTRA_LIFE: // EXTRA_LIFE
                printf("Extra Life\n");
                extra_life = true;
                ClearConsole(score, level);
                break;
            case SCORE_MULTIPLIER: // SCORE_MULTIPLIER
                score_multiplier = (rand() % 3) + 2;
                printf("%ix Score Multiplier\n", score_multiplier);
                break;
            case LIGHTNING_ROUND: // LIGHTNING_ROUND
                printf("Lightning Round\n");
                time_multiplier = 0.5f;
                break;
            default:
                break;
            }
            Sleep(1000);
            ClearConsole(score, level);
        }

        int** simon_numbers = AllocateArray(dimensions, difficulty);
        PopulateList(dimensions, difficulty, simon_numbers);

        for (int i = 0; i < dimensions; i++) {
            for (int j = 0; j < difficulty; j++) {
                printf("%i  ", simon_numbers[i][j]);
                Sleep((int)(500 * time_multiplier));
            }
            Sleep((int)(2000 * time_multiplier));
            ClearConsole(score, level);
            printf("\n");
        }
        int flattened_array[dimensions * difficulty];
        FlattenArray(simon_numbers, dimensions, difficulty, flattened_array);
        FreeArray(simon_numbers, dimensions);

        ClearConsole(score, level);
        Sleep((int)(1000 * time_multiplier));

        printf("Enter the sequence, separated by commas:\n");
        time_multiplier = 1.0f;

        char buffer[100];
        memset(buffer, 0, 100);
        fgets(buffer, 100, stdin);
        int result = CompareAnswer(buffer, flattened_array, dimensions * difficulty);
        if (result == 1) {
            printf("Good job! Moving to level %i\n", ++level);
            if (event == DOUBLE_OR_NOTHING) {
                score = score * 2;
            }
            else {
                score = ++score * score_multiplier;
            }
            if (rand() % 3 == 0) {
                event = StartEvent();
                event_active = true;
            } else {
                event_active = false;
            }
        } else if (result == 0) {
            printf("Incorrect! Repeating level %i\n", level); --difficulty;
            if (extra_life) {
                Sleep(250);
                printf("Extra life is no longer active");
                extra_life = false;
            }
            else if (event == 1) { // DOUBLE_OR_NOTHING
                score = 0;
            }
            else {
                score = score - (1 * score_multiplier);
            }
        } else {
            printf("Invalid character(s)! Try again\n"); --difficulty;
        }
        Sleep(2000);
        ClearConsole(score, level);
        score_multiplier = 1;
    }
    printf("Final Score: %d", score);
    Sleep(5000);
    return 0;
}
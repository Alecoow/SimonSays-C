#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#include "main.h"

enum POWERUPS { //TODO: implement
    POWERUP_REVEAL = 1,
    POWERUP_RESHUFFLE = 1 << 1,
    POWERUP_DOUBLE_POINTS = 1 << 2,
};

int main(void) {
    srand(time(NULL));
    int dimensions = 1;
    for (int level = 1; level < 11; level++) {
        dimensions += !(level % 5); // every third level should increase the dimensions of the game. Final product could have user memorize grid then pick certain numbers from it, using powerups if its too difficult
        char** simon_numbers = malloc(dimensions * sizeof(char*));
        for (int i = 0; i < dimensions; i ++) {
            simon_numbers[i] = malloc(level * sizeof(int));
        }
        PopulateList(dimensions, level, simon_numbers);
        for (int i = 0; i < dimensions; i++) {
            for (int j = 0; j < level; j++) {
                setbuf(stdout, NULL);
                printf("%d\n", simon_numbers[i][j]);
            }
        }
        char flattened_array[dimensions*level];
        FlattenArray(simon_numbers, dimensions, level, flattened_array);
        free(simon_numbers);

        Sleep(1500);
        system("cls");
        Sleep(1000);

        printf("Enter the sequence, separated by commas:\n");

        char buffer[100];
        memset(buffer, 0, 100);
        fgets(buffer, 100, stdin);
        if (CompareAnswer(buffer, flattened_array, dimensions*level)) {
            printf("Good job! Moving to level %d\n", level + 1);
            Sleep(2500);
            system("cls");
        } else {
            printf("Incorrect! You made it to level %d\n", level);
            return 1;
        }

    }
    return 0;
}
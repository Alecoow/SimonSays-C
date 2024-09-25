#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define WIN32_LEAN_AND_MEAN;
#include "main.h"

void GenerateList(const int dimensions,const int size, int** list) {
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < size; j++) {
            list[i][j] = (rand() % 10);
        }
    }
}

char* FilterAnswer(char input[], int size) {
    const char* trunc = strtok(input, ", \n");
    char* new_string = malloc((size+1) * sizeof(char));
    new_string[0] = '\0';
    while (trunc != NULL) {
        strcat(new_string, trunc);
        trunc = strtok(nullptr, ", \n");
    }
    return new_string;
}

bool CompareAnswer(char* input, const int* answer, int size_of_input, int size_of_answer) {
    char* filtered = FilterAnswer(input, size_of_input);
    int* input_numbers = malloc((size_of_answer+1) * sizeof(int));

    for (int i = 0; i < size_of_answer; i++) {
        input_numbers[i] = filtered[i] - '0';
    }

    bool result = true;
    for (int i = 0; i < size_of_answer; i++) {
        if (input_numbers[i] != answer[i]) {
            result = false;
            break;
        }
    }

    free(filtered);
    free(input_numbers);
    return result;
}

int* GenerateMapDimension(const int size) {
    int* map = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        map[i] = malloc(size * sizeof(int));
    }
    return map;
}

void Flatten(void* array, int* dimensions, int current_dim, int* flat_array, int* index) {
    if (current_dim == 1) {
        int* arr = array;
        for (int i = 0; i < dimensions[0]; i++) {
            flat_array[(*index)++] = arr[i];
        }
    } else {
        void** arr = array;
        for (int i = 0; i < dimensions[0]; i++) {
            Flatten(arr[i], dimensions + 1, current_dim - 1, flat_array, index);
        }
    }
}

int* ReformatVector(void* array, int* dimensions, int num_dimensions) {
    int size = 1;
    for (int i = 0; i < num_dimensions; i++) {
        size *= dimensions[i];
    }

    int* flat_array = malloc(size * sizeof(int));

    int index = 0;
    Flatten(array, dimensions, num_dimensions, flat_array, &index);

    return flat_array;
}

enum POWERUPS { //TODO: implement
    POWERUP_REVEAL = 0,
    POWERUP_RESHUFFLE = 0 << 1,
    POWERUP_DOUBLE_POINTS = 0 << 2,
};

int main(void) {
    srand(time(nullptr));
    for (int level = 1; level < 11; level++) {
        int dimensions = level % 2; // every other level should increase the dimensions of the game. Final product could have user memorize grid then pick certain numbers from it, using powerups if its too difficult
        int simon_numbers[level][dimensions];
        GenerateList(dimensions, level, simon_numbers);
        for (int i = 0; i < level; i++) {
            for (int j = 0; j <= dimensions; j++)
            setbuf(stdout, nullptr);
            printf("%d\n", simon_numbers[dimensions][i]);
        }
        Sleep(1500);
        system("cls");
        Sleep(1000);

        printf("Enter the sequence, separated by commas:\n");

        char input[100];
        scanf("%99s", input);
        if (CompareAnswer(input, simon_numbers, level, strlen(input))) {
            printf("Good job! Moving to level %d\n", level + 1);
            Sleep(2500);
            system("cls");
        } else {
            printf("Incorrect! You made it to level %d\n");
            return 2;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define WIN32_LEAN_AND_MEAN;

void GenerateList(int size, int* list) {
    for (int i = 0; i < size; i++) {
        list[i] = (rand() % 10);
    }
}

char* FilterAnswer(char input[], int size) {

    const char* trunc = strtok(input, ", \n");
    char* new_string = malloc((size+1) * sizeof(char));
    new_string[0] = '\0';
    while (trunc != NULL) {
        strcat(new_string, trunc);
        trunc = strtok(NULL, ", \n");
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

int** GenerateMap(const int size) {
    int** map = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        map[i] = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            map[i][j] = (rand() % 10);
        }
    }
    return map;
}

void FreeMap(int** map, const int size) {
    for (int i = 0; i < size; i++) {
        free(map[i]);
    }
}

enum POWERUPS { //TODO: implement
    POWERUP_REVEAL = 0,
    POWERUP_RESHUFFLE = 0 << 1,
    POWERUP_DOUBLE_POINTS = 0 << 2,
};

int main(void) {

    srand(time(NULL));
    for (int level = 1; level != 10; level++) {
        int dimensions = level % 2; // every other level should increase the dimensions of the game. Final product could have user memorize grid then pick certain numbers from it, using powerups if its too difficult
        printf("dimensions: %d", dimensions);
        int simon_numbers[dimensions][level];
        GenerateList(level, simon_numbers);
        for (int i = 0; i < level; i++) {
            setbuf(stdout, nullptr); // workaround for bug in Clion that prevents output while debugging
            printf("%d\n", simon_numbers[i]);
            Sleep(1500);
            system("cls");
        }
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

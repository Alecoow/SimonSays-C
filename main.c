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

    const char* trunc = strtok(input, ",\n");
    char* new_string = malloc(size * sizeof(char));
    new_string[0] = '\0';
    while (trunc != NULL) {
        strcat(new_string, trunc);
        trunc = strtok(NULL, ",\n");
    }
    char* output = new_string;
    free(new_string);
    return output;

}

bool CompareAnswer(char* input, int* answer, int size_of_input, int size_of_answer) {
    //convert string input to integer input, then compare to answer
    char* filtered = FilterAnswer(input, size_of_input);
    //for (int i = 0; i <) {}
    return true;
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

enum POWERUPS {
    POWERUP_REVEAL = 0,
    POWERUP_RESHUFFLE = 0 << 1,
    POWERUP_DOUBLE_POINTS = 0 << 2,
};

int main(void) {

    srand(time(NULL));
    for (int level = 1; level != 10; level++) {
        int simon_numbers[level];
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

        char input[sizeof(int)];
        scanf(input);

        if (CompareAnswer) {
            printf("Good job! Moving to level %d\n", level + 1);
            Sleep(2500);
            system("cls");
        }



    }

    return 0;
}

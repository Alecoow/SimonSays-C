#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>

int** AllocateArray(int dimensions, int difficulty) {
    int** data = malloc(sizeof(int*) * dimensions);
    for (int i = 0; i < dimensions; i++) {
        data[i] = malloc(sizeof(int) * difficulty);
    }
    return data;
}

void FreeArray(int** data, int dimensions, int difficulty) {
    for (int i = 0; i < dimensions; i++) {
        free(data[i]);
    }
    free(data);
}

void ClearConsole(int score) {
    system("cls");
    char score_buffer[24];
    sprintf_s(score_buffer, sizeof(score_buffer), "Score: %d", score);
    int score_offset = strlen(score_buffer);
    printf("\x1b[0;%iH", 120-score_offset);
    printf("%s\n", score_buffer);
    printf("\x1b[0;80H");
    printf("PowerUps: %s", "");
    printf("\x1b[H");
}

void PopulateList(const int dimensions, const int size, int** list) {
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < size; j++) {
            list[i][j] = (rand() % 10);
        }
    }
}

int FilterAnswer(char* input, int size) {
    const char* trunc = strtok(input, ", \n");
    char* new_string = malloc((size+1) * sizeof(char));
    new_string[0] = '\0';
    while (trunc != NULL) {
        strcat(new_string, trunc);
        trunc = strtok(NULL, ", \n");
    }
    int new_string_len = strlen(new_string);
    if (new_string_len > size) {
        return 1;
    }
    for (int i = 0; i < new_string_len; i++) {
        new_string[i] = (new_string[i] - '0');
        input[i] = new_string[i];
    }
    free(new_string);
    return 0;
}
int SanitizeString(const char* string) {
    for (int i = 0; i < strlen(string) - 1; i++) {
        if (string[i] == '\0' || string[i] == '\n') {
            break;
        }

        if (!isdigit(string[i]) && string[i] != ' ' && string[i] != ',') {
            return 0;
        }
    }
    return 1;
}

int CompareAnswer(char* input, int* answer, int size_of_input) {
    if (!SanitizeString(input)) {
        return -1;
    }
    int filter_result = FilterAnswer(input, size_of_input);
    if (filter_result) {
        return -1;
    }
    for (int i = 0; i < size_of_input; i++) {
        if (input[i] != answer[i]) {
            return 0;
        }
    }
    return 1;
}

// Convert 2D array to a 1 dimensional array
void FlattenArray(int** array, int dimensions, int elements, int* output) {
    int index = 0;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < elements; j++) {
            output[index++] = array[i][j];
        }
    }
}

enum POWERUPS { //TODO: implement
    POWERUP_REVEAL = 1, // activate to reveal the correct answer
    POWERUP_RESHUFFLE = 1 << 1, // activate to replay the same level but with different numbers
    POWERUP_DOUBLE_POINTS = 1 << 2, // activate to either twice the score if correct, or reset the score to 0
};

int GetRandomPowerup() {
    int powerups[] = {POWERUP_REVEAL, POWERUP_RESHUFFLE, POWERUP_DOUBLE_POINTS};
    int random_index = rand() % 3;
    return powerups[random_index];
}

#endif //MAIN_H
#ifndef MAIN_H
#define MAIN_H
#endif //MAIN_H

int** AllocateArray(int dimensions, int difficulty) {
    int** data = malloc(sizeof(int*) * dimensions);
    for (int i = 0; i < dimensions; i++) {
        data[i] = malloc(sizeof(int) * difficulty);
    }
    return data;
}

void FreeArray(int** data, int dimensions) {
    for (int i = 0; i < dimensions; i++) {
        free(data[i]);
    }
    free(data);
}

void ClearConsole(int score, int level) {
    system("cls");
    char score_buffer[24];
    sprintf_s(score_buffer, sizeof(score_buffer), "Score: %d", score);
    int score_offset = strlen(score_buffer);
    printf("\x1b[0;%iH", 120-score_offset);
    printf("%s\n", score_buffer);
    printf("\x1b[0;80H");
    printf("Level: %d", level);
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
        free(new_string);
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
enum CHALLENGES {
    NO_CHALLENGE = 1 << 0,
    DOUBLE_OR_NOTHING = 1 << 1,
    EXTRA_LIFE = 1 << 2,
    SCORE_MULTIPLIER = 1 << 3,
    LIGHTNING_ROUND = 1 << 4
};

int StartEvent() {
    int events[] = {DOUBLE_OR_NOTHING, EXTRA_LIFE, SCORE_MULTIPLIER, LIGHTNING_ROUND};
    int random_index = rand() % 4;
    return events[random_index];
}
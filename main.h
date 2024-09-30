#ifndef MAIN_H
#define MAIN_H

#endif //MAIN_H

void PopulateList(const int dimensions, const int size, char** list) {
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < size; j++) {
            list[i][j] = (rand() % 10);
        }
    }
}

void FilterAnswer(char* input, int size) {
    const char* trunc = strtok(input, ", \n");
    char* new_string = malloc((size+1) * sizeof(char));
    new_string[0] = '\0';
    while (trunc != NULL) {
        strcat(new_string, trunc);
        trunc = strtok(NULL, ", \n");
    }
    for (int i = 0; i < strlen(new_string); i++) {
        new_string[i] = (new_string[i] - '0');
        input[i] = new_string[i];
    }
    free(new_string);
}

bool CompareAnswer(char* input, char* answer, int size_of_input) {
    FilterAnswer(input, size_of_input);

    bool result = true;
    for (int i = 0; i < size_of_input; i++) {
        if (input[i] != answer[i]) {
            result = false;
            break;
        }
    }
    return result;
}

// Convert 2D array to a 1 dimensional array
void FlattenArray(char** array, int dimensions, int elements, char* output) {
    int index = 0;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < elements; j++) {
            output[index++] = array[i][j];
        }
    }
}
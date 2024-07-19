#include "strings_methods.h"
#include <stdio.h>
#include <string.h>

StringArray split_string(const char var[], const char *delimiter, size_t *array_size) {
    char **strings_array = NULL;
    size_t capacity = 10; 
    *array_size = 0;

    strings_array = malloc(capacity * sizeof(char *));
    if (strings_array == NULL) {
        perror("Failed to allocate memory for strings_array array");
        return NULL;
    }

    char *var_copy = strdup(var);
    if (var_copy == NULL) {
        perror("Failed to allocate memory for string copy");
        free(strings_array);
        return NULL;
    }

    char *token = strtok(var_copy, delimiter);
    while (token != NULL) {
        if (*array_size >= capacity) {
            capacity *= 2; // Double the capacity
            char **temp = realloc(strings_array, capacity * sizeof(char *));
            if (temp == NULL) {
                perror("Failed to reallocate memory for strings_array array");
                for (size_t i = 0; i < *array_size; i++) {
                    free(strings_array[i]);
                }
                free(strings_array);
                free(var_copy);
                return NULL;
            }
            strings_array = temp;
        }

        strings_array[*array_size] = strdup(token);
        if (strings_array[*array_size] == NULL) {
            perror("Failed to duplicate token");
            for (size_t i = 0; i < *array_size; i++) {
                free(strings_array[i]);
            }
            free(strings_array);
            free(var_copy);
            return NULL;
        }
        (*array_size)++;
        token = strtok(NULL, delimiter);
    }

    free(var_copy);

    return strings_array;
}

char *copy_string_from_array(StringArray array, size_t index) {
    if (array == NULL || index < 0) {
        fprintf(stderr, "Invalid array or index\n");
        return NULL;
    }

    size_t string_length = strlen(array[index]);

    char *copied_string = malloc((string_length + 1) * sizeof(char)); // +1 for null terminator
    if (copied_string == NULL) {
        perror("Failed to allocate memory for copied string");
        return NULL;
    }

    strcpy(copied_string, array[index]);

    return copied_string;
}

char *remove_index_from_array(StringArray array, size_t index, size_t *array_length) {
    if (array == NULL || index < 0 || index >= *array_length) {
        fprintf(stderr, "Invalid array or index\n");
        return NULL;
    }

    char *removed_string = copy_string_from_array(array, index);
    if (removed_string == NULL) {
        fprintf(stderr, "Failed to copy string from array\n");
        return NULL;
    }

    free(array[index]);

    for (size_t i = index; i < *array_length - 1; i++) {
        array[i] = array[i + 1];
    }

    (*array_length)--;

    return removed_string;
}

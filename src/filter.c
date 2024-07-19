#include "filter_methods.h"
#include "strings_methods.h"
#include <stdio.h>
#include <string.h>

#define MAX_OPERATOR_LENGTH 4

Filter *parse_to_filters_struct(const char *filter_str, size_t *num_filters) {
    if (filter_str == NULL || num_filters == NULL) {
        fprintf(stderr, "Invalid arguments for parsing filters\n");
        return NULL;
    }

    size_t filter_count = 0;
    StringArray filter_lines = split_string(filter_str, "\n", &filter_count);
    if (filter_lines == NULL || filter_count == 0) {
        fprintf(stderr, "Failed to split filter string\n");
        return NULL;
    }

    Filter *filters = malloc(filter_count * sizeof(Filter));
    if (filters == NULL) {
        perror("Failed to allocate memory for filters");
        free(filter_lines);
        return NULL;
    }

    for (size_t i = 0; i < filter_count; ++i) {
        char *filter_line = filter_lines[i];
        char *operator_pos = NULL;

        if ((operator_pos = strstr(filter_line, "!=")) != NULL) {
            strncpy(filters[i].operator, "!=", MAX_OPERATOR_LENGTH);
        } else if ((operator_pos = strstr(filter_line, "<=")) != NULL) {
            strncpy(filters[i].operator, "<=", MAX_OPERATOR_LENGTH);
        } else if ((operator_pos = strstr(filter_line, ">=")) != NULL) {
            strncpy(filters[i].operator, ">=", MAX_OPERATOR_LENGTH);
        } else if ((operator_pos = strstr(filter_line, ">")) != NULL) {
            strncpy(filters[i].operator, ">", MAX_OPERATOR_LENGTH);
        } else if ((operator_pos = strstr(filter_line, "<")) != NULL) {
            strncpy(filters[i].operator, "<", MAX_OPERATOR_LENGTH);
        } else if ((operator_pos = strstr(filter_line, "=")) != NULL) {
            strncpy(filters[i].operator, "=", MAX_OPERATOR_LENGTH);
        } else {
            fprintf(stderr, "Invalid filter format: %s\n", filter_line);
            free_filters(filters, filter_count);
            free(filter_lines);
            return NULL;
        }

        *operator_pos = '\0'; 
        filters[i].header = strdup(filter_line);
        filters[i].value = atoi(operator_pos + strlen(filters[i].operator));
    }

    *num_filters = filter_count;

    for (size_t i = 0; i < filter_count; ++i) {
        free(filter_lines[i]);
    }
    free(filter_lines);

    return filters;
}



// Function to free memory allocated for Filter array
void free_filters(Filter *filters, size_t num_filters) {
    if (filters == NULL) {
        return;
    }

    for (size_t i = 0; i < num_filters; ++i) {
        free(filters[i].header);
    }
    free(filters);
}

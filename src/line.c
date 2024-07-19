#include "memory_management.h"
#include "header_methods.h"
#include "filter_methods.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

bool apply_filter(const int column_value, const char *operator, const int filter_value) {
    if (strcmp(operator, "=") == 0) {
        return column_value == filter_value;
    }
    if (strcmp(operator, ">") == 0) {
        return column_value > filter_value;
    }
    if (strcmp(operator, "<") == 0) {
        return column_value < filter_value;
    }
    if (strcmp(operator, ">=") == 0) {
        return column_value >= filter_value;
    }
    if (strcmp(operator, "<=") == 0) {
        return column_value <= filter_value;
    }
    if (strcmp(operator, "!=") == 0) {
        return column_value != filter_value;
    }    
    
    fprintf(stderr, "Unrecognized operator: %s\n", operator);
    return false;  
}

bool validate_line(const char line[], const CsvResources *resources) {
    size_t num_columns;
    StringArray columns = split_string(line, ",", &num_columns);
    if (columns == NULL) {
        fprintf(stderr, "Failed to split CSV line\n");
        return false;
    }

    for (size_t i = 0; i < resources->filters_quantity; i++) {
        const Filter *filter = &resources->filters_struct[i];
        size_t column_index = find_header_position_in_dict(resources->header_positions, filter->header);
        if (column_index == SIZE_MAX) {
            fprintf(stderr, "Header '%s' not found in CSV headers\n", filter->header);
            for (size_t j = 0; j < num_columns; j++) {
                free(columns[j]);
            }
            free(columns);
            return false;
        }

        int column_value = atoi(columns[column_index]);

        if (!apply_filter(column_value, filter->operator, filter->value)) {
            for (size_t j = 0; j < num_columns; j++) {
                free(columns[j]);
            }
            free(columns);
            return false;
        }
    }

    for (size_t i = 0; i < num_columns; i++) {
        free(columns[i]);
    }
    free(columns);

    return true;
}

void append_to_result(CsvResources *resources, const char *str) {
    size_t str_length = strlen(str);

    if (resources->result_length + str_length + 1 > resources->result_capacity) {
        size_t new_capacity = resources->result_capacity;
        while (resources->result_length + str_length + 1 > new_capacity) {
            new_capacity *= 2; 
        }
        
        char *new_result = realloc(resources->result, new_capacity);
        if (new_result == NULL) {
            fprintf(stderr, "Failed to reallocate memory for result\n");
            exit(EXIT_FAILURE);
        }
        resources->result = new_result;
        resources->result_capacity = new_capacity; 
    }

    strcpy(resources->result + resources->result_length, str);
    resources->result_length += str_length;
}

void print_right_columns(const char line[], const char columns_to_print[], CsvResources *resources) {
    size_t num_columns;
    StringArray columns = split_string(line, ",", &num_columns);
    if (columns == NULL) {
        fprintf(stderr, "Failed to split CSV line\n");
        return;
    }

    size_t num_headers;
    StringArray headers = split_string(columns_to_print, ",", &num_headers);
    if (headers == NULL) {
        fprintf(stderr, "Failed to split headers_output\n");
        for (size_t i = 0; i < num_columns; i++) {
            free(columns[i]);
        }
        free(columns);
        return;
    }

    for (size_t i = 0; i < num_headers; i++) {
        size_t column_index = find_header_position_in_dict(resources->header_positions, headers[i]);
        if (column_index == SIZE_MAX) {
            fprintf(stderr, "Header '%s' not found in CSV headers\n", headers[i]);
            continue;
        }

        append_to_result(resources, columns[column_index]);


        if (i < num_headers - 1) {
            append_to_result(resources, ",");
        }
    }

    append_to_result(resources, "\n");

    for (size_t i = 0; i < num_columns; i++) {
        free(columns[i]);
    }
    free(columns);

    for (size_t i = 0; i < num_headers; i++) {
        free(headers[i]);
    }
    free(headers);
}
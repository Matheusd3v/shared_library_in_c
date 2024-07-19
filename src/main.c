#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_management.h"
#include "filter_methods.h"
#include "header_methods.h"
#include "line_methods.h"
#include "strings_methods.h"
#include <time.h>

#define INITIAL_BUFFER_SIZE 1024

void processCsv(const char lines[], const char headers_output[], const char filter[]) {
    CsvResources resources = {NULL, 0, NULL, NULL, 0};

    resources.csv_lines = split_string(lines, "\n", &resources.csv_lines_quantity);
    if (resources.csv_lines == NULL) {
        fprintf(stderr, "Failed to split CSV data into lines\n");
        return;
    }

    char *header_line = resources.csv_lines[0];
    resources.header_positions = create_header_dict(header_line, ",");
    if (resources.header_positions == NULL) {
        fprintf(stderr, "Failed to create header dictionary\n");
        cleanup_resources(&resources);
        return;
    }

    char *header_error_message = validate_headers_output(headers_output, &resources);
    if (header_error_message && strlen(header_error_message) > 0) {
        fprintf(stderr, "%s\n", header_error_message); 
        free(header_error_message); 
        cleanup_resources(&resources);
        return;
    }

    const char *columns_to_print = (headers_output[0] == '\0') ? header_line : headers_output;
    if (columns_to_print == NULL) {
        fprintf(stderr, "Invalid columns to print\n");
        cleanup_resources(&resources);
        return;
    }

    resources.filters_struct = parse_to_filters_struct(filter, &resources.filters_quantity);
    if (resources.filters_struct == NULL) {
        fprintf(stderr, "Failed to parse filter string\n");
        cleanup_resources(&resources);
        return;
    }

    char *filter_error_message = validate_header_in_filters(&resources);
    if (filter_error_message && strlen(filter_error_message) > 0) {
        fprintf(stderr, "%s\n", filter_error_message); 
        free(filter_error_message); 
        cleanup_resources(&resources);
        return;
    }

    resources.result_capacity = INITIAL_BUFFER_SIZE; 
    resources.result = malloc(resources.result_capacity);
    if (resources.result == NULL) {
        fprintf(stderr, "Failed to allocate memory for result\n");
        cleanup_resources(&resources);
        return;
    }
    resources.result_length = 0; 

    append_to_result(&resources, columns_to_print);
    append_to_result(&resources, "\n"); 

    for (size_t i = 1; i < resources.csv_lines_quantity; i++) {
        const char *line = resources.csv_lines[i];
        if (validate_line(line, &resources)) {
            print_right_columns(line, columns_to_print, &resources);
        }
    }

    printf("%s", resources.result);

    cleanup_resources(&resources);
}


void processCsvFile(const char *filepath, const char *headers_output, const char *filter) {
    CsvResources resources = {NULL, 0, NULL, NULL, 0};
    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    resources.result_capacity = INITIAL_BUFFER_SIZE; 
    resources.result = malloc(resources.result_capacity);
    if (resources.result == NULL) {
        fprintf(stderr, "Failed to allocate memory for result\n");
        fclose(file);
        free(line);
        return;
    }
    resources.result_length = 0; 

    if ((read = getline(&line, &len, file)) != -1) {
        line[strcspn(line, "\r\n")] = '\0';
        resources.header_positions = create_header_dict(line, ",");
        if (resources.header_positions == NULL) {
            fprintf(stderr, "Failed to create header dictionary\n");
            fclose(file);
            free(line);
            return;
        }

        resources.headers = strdup(line);
        if (resources.headers == NULL) {
            fprintf(stderr, "Failed to duplicate headers\n");
            fclose(file);
            free(line);
            return;
        }
    } else {
        fprintf(stderr, "Failed to read header line\n");
        fclose(file);
        free(line);
        return;
    }


    char *header_error_message = validate_headers_output(headers_output, &resources);
    if (header_error_message && strlen(header_error_message) > 0) {
        fprintf(stderr, "%s\n", header_error_message); 
        free(header_error_message); 
        cleanup_resources(&resources);
        return;
    }

    const char *columns_to_print = (headers_output[0] == '\0') ? resources.headers : headers_output;

    resources.filters_struct = parse_to_filters_struct(filter, &resources.filters_quantity);
    if (resources.filters_struct == NULL) {
        fprintf(stderr, "Failed to parse filter string\n");
        cleanup_resources(&resources);
        fclose(file);
        free(line);
        return;
    }

    char *filter_error_message = validate_header_in_filters(&resources);
    if (filter_error_message && strlen(filter_error_message) > 0) {
        fprintf(stderr, "%s\n", filter_error_message); 
        free(filter_error_message); 
        cleanup_resources(&resources);
        return;
    }

    append_to_result(&resources, columns_to_print);
    append_to_result(&resources, "\n");

    while ((read = getline(&line, &len, file)) != -1) {
        line[strcspn(line, "\r\n")] = '\0';
        if (validate_line(line, &resources)) {
            print_right_columns(line, columns_to_print, &resources);
        }
    }

    printf("%s", resources.result);

    cleanup_resources(&resources);
    fclose(file);
    free(line);
}


#ifndef TEST_BUILD
int main(void) {
    return 0;
}
#endif
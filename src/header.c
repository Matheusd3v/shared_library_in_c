#include "header_methods.h"
#include "memory_management.h"
#include "strings_methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>

static size_t hash(const char *key) {
    size_t hash_value = 0;
    while (*key) {
        hash_value = (hash_value << 5) + *key++;
    }
    return hash_value % HASH_MAP_SIZE;
}

HeaderDictionary *create_header_dict(const char *headers, const char *delimiter) {
    if (headers == NULL || delimiter == NULL) {
        fprintf(stderr, "Invalid headers or delimiter\n");
        return NULL;
    }

    HeaderDictionary *dict = malloc(sizeof(HeaderDictionary));
    if (dict == NULL) {
        perror("Failed to allocate memory for HeaderDictionary");
        return NULL;
    }

    dict->bucket_count = HASH_MAP_SIZE;
    dict->buckets = calloc(dict->bucket_count, sizeof(HeaderPositionNode *));
    if (dict->buckets == NULL) {
        perror("Failed to allocate memory for hash map buckets");
        free(dict);
        return NULL;
    }

    size_t num_tokens;
    StringArray tokens = split_string(headers, delimiter, &num_tokens);
    if (tokens == NULL) {
        free(dict->buckets);
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < num_tokens; i++) {
        size_t index = hash(tokens[i]);
        HeaderPositionNode *new_node = malloc(sizeof(HeaderPositionNode));
        if (new_node == NULL) {
            perror("Failed to allocate memory for hash map node");
            free(tokens);
            free(dict->buckets);
            free(dict);
            return NULL;
        }
        new_node->data.name = strdup(tokens[i]);
        new_node->data.position = i;
        new_node->next = dict->buckets[index];
        dict->buckets[index] = new_node;
    }

    for (size_t i = 0; i < num_tokens; i++) {
        free(tokens[i]);
    }
    free(tokens);

    return dict;
}

size_t find_header_position_in_dict(const HeaderDictionary *dict, const char *header_name) {
    if (dict == NULL || header_name == NULL) {
        fprintf(stderr, "Invalid dictionary or header name\n");
        return SIZE_MAX;
    }

    size_t index = hash(header_name);
    HeaderPositionNode *current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->data.name, header_name) == 0) {
            return current->data.position;
        }
        current = current->next;
    }

    return SIZE_MAX;
}


void free_header_dict(HeaderDictionary *dict) {
    if (dict == NULL) {
        return;
    }

    for (size_t i = 0; i < dict->bucket_count; i++) {
        HeaderPositionNode *current = dict->buckets[i];
        while (current != NULL) {
            HeaderPositionNode *temp = current;
            current = current->next;
            free((char *)temp->data.name);
            free(temp);
        }
    }

    free(dict->buckets);
    free(dict);
}

char *validate_headers_output(const char *headers_output, const CsvResources *resources) {
    if (headers_output == NULL || strlen(headers_output) == 0) {
        return strdup(""); 
    }
    size_t num_headers;
    StringArray headers_to_validate = split_string(headers_output, ",", &num_headers);
    if (headers_to_validate == NULL) {
        fprintf(stderr, "Failed to split headers_output\n");
        return strdup("Error: Failed to split headers_output");
    }

    for (size_t i = 0; i < num_headers; i++) {
        const char *header = headers_to_validate[i];
        if (find_header_position_in_dict(resources->header_positions, header) == SIZE_MAX) {
            size_t message_length = strlen(header) + strlen("Header '' not found in CSV file/string") + 1; // +1 for null terminator
            char *error_message = malloc(message_length);
            if (error_message != NULL) {
                strcpy(error_message, "Header '");
                strcat(error_message, header);
                strcat(error_message, "' not found in CSV file/string");
                free(headers_to_validate);
                return error_message; 
            }
        }
    }

    free(headers_to_validate);

    return strdup("");
}



char* validate_header_in_filters(const CsvResources *resources) {
    for (size_t i = 0; i < resources->filters_quantity; i++) {
        const char *filter_header = resources->filters_struct[i].header;

        if (find_header_position_in_dict(resources->header_positions, filter_header) == SIZE_MAX) {
            char *error_message = malloc(256);
            if (error_message != NULL) {
                snprintf(error_message, 256, "Header %s not found in CSV file/string", filter_header);
                return error_message; 
            }
        }
    }

    return strdup("");    
}
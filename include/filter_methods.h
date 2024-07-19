#ifndef FILTER_METHODS_H_
#define FILTER_METHODS_H_

#include <stdlib.h>


// Struct to hold filter information
typedef struct {
    char *header; // Pointer to dynamically allocated memory for header name
    char operator[4]; // Assuming operator length is up to 3 characters (+ null terminator)
    int value;
} Filter;


/**
 * Function to initialize an array of Filter structs and parse filter data from a string.
 *
 * @param filter_str String containing filter data to parse.
 * @param num_filters Pointer to store the number of filters parsed.
 * @return Filter* Array of Filter structs initialized and populated with filter data.
 */
Filter *parse_to_filters_struct(const char *filter_str, size_t *num_filters);


/**
 *  Function to free memory allocated for Filter array
 *  @param filters Array of Filter structs
 *  @param num_filters Quantity of filters
 *  @return void
 */
void free_filters(Filter *filters, size_t num_filters);

#endif /* FILTER_METHODS_H_ */
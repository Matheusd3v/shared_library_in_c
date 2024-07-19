#ifndef MEMORY_MANAGEMENT_H_
#define MEMORY_MANAGEMENT_H_

#include "header_methods.h"
#include "strings_methods.h"
#include "filter_methods.h"
#include <stdlib.h>

typedef struct CsvResources CsvResources;

// Struct to manage better memory allocation
typedef struct CsvResources {
    StringArray csv_lines;
    char *headers;
    HeaderDictionary *header_positions;
    Filter *filters_struct;
    size_t filters_quantity;
    size_t csv_lines_quantity;
    size_t result_capacity;  // Improved name for size
    size_t result_length;    // Improved name for length
    char *result;            // Result buffer    
} CsvResources;

/**
 *  Function to clean csv resources in main function
 *  @param resources A struct of CsvResources with all resources
 *  @return void
 */
void cleanup_resources(CsvResources *resources);

#endif /* MEMORY_MANAGEMENT_H_ */
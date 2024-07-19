#ifndef HEADER_METHODS_H_
#define HEADER_METHODS_H_

#include <stdlib.h>

typedef struct CsvResources CsvResources; 

#define HASH_MAP_SIZE 100

/**
 * Struct to map header names to their positions in CSV headers.
 */
typedef struct {
    const char *name;
    size_t position;
} HeaderPosition;

/**
 * Hash map node structure for Header Positions
 */
typedef struct HeaderPositionNode {
    HeaderPosition data;
    struct HeaderPositionNode *next;
} HeaderPositionNode;

/**
 * Hash map structure for Header Positions
 */
typedef struct {
    HeaderPositionNode **buckets;  // Array of linked list nodes
    size_t bucket_count;           // Number of buckets
} HeaderDictionary;

/**
 * Function to create a mapping of header names to their positions in a CSV header line
 * using a hash map structure.
 *
 * @param headers The CSV header line containing header names.
 * @param delimiter The delimiter used in the CSV header line (e.g., ",").
 * @return HeaderDictionary* Hash map of HeaderPosition structs mapping header names to positions.
 */
HeaderDictionary *create_header_dict(const char *headers, const char *delimiter);


/**
 * Function to find the position of a header by its name in the HeaderDictionary.
 *
 * @param dict Hash map of HeaderPosition structs mapping header names to positions.
 * @param header_name The name of the header to find.
 * @return size_t Position of the header in the CSV headers, or SIZE_MAX if not found.
 */
size_t find_header_position_in_dict(const HeaderDictionary *dict, const char *header_name);


/**
 * Function to free memory allocated for a HeaderDictionary.
 *
 * @param dict Dictionary of HeaderPosition structs to free.
 */
void free_header_dict(HeaderDictionary *dict);

/**
 * Function to validate the headers_output by checking if all headers exist in the resources headers.
 *
 * @param headers_output The headers to be validated.
 * @param resources The CsvResources structure containing the existing headers.
 * @return char*
 */
char *validate_headers_output(const char *headers_output, const CsvResources *resources);


/**
 *  Function to validate if filter struc have valid header
 *  @param resources CsvResources
 *  @return char*
 */
char* validate_header_in_filters(const CsvResources *resources);

#endif /* HEADER_METHODS_H_ */
#ifndef LINE_METHODS_H_
#define LINE_METHODS_H_

#include "header_methods.h"
#include "memory_management.h"
#include <stdbool.h>

/**
 *  Function to validate line applying filters
 *  @param line The csv line string with delimiter
 *  @param resources CsvResources - All csv resources
 *  @return bool 
 */
bool validate_line(const char line[], const CsvResources *resources);


/**
 *  Function to compare line columns by operator
 *  @param column_value The value of column at index/header X
 *  @param operator The string operator e.g "<", "=", ">="
 *  @param filterThe The value after filter operator
 *  @return bool 
 */
bool apply_filter(const int column_value, const char *operator, const int filter_value);


/**
 *  Function to print line columns selected in params of processCsv or processCsvFile
 *  @param line The entire csv line validated after applyed filters
 *  @param headers_output The headers selected to print 
 *  @param resources CsvResources with result fields
 *  @return void
 */
void print_right_columns(const char line[], const char columns_to_print[], CsvResources *resources);

/**
 *  Function to append header and valid column lines to unique string
 *  @param resources All csv shared resources with result fields
 *  @param str String or line to append
 *  @return void
 */
void append_to_result(CsvResources *resources, const char *str);

#endif /* LINE_METHODS_H_ */
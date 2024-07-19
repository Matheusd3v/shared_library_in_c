#ifndef STRING_METHODS_H_
#define STRING_METHODS_H_


#include <stdlib.h>

typedef char **StringArray;

/**
 * Function to split a string by a delimiter.
 *
 * @param var The string to be split.
 * @param delimiter The symbol in the string to split by, e.g., ","
 * @param arr_size Pointer to store the size of the resulting array.
 * 
 * @return StringArray An array of strings resulting from the split.
 */
StringArray split_string(const char var[], const char *delimiter, size_t *arr_size);

/**
 * Function to copy a string from a StringArray at a specified index.
 *
 * @param arr The array of strings from which to copy.
 * @param index The index of the string to copy.
 * @return char* The copied string (dynamically allocated).
 */
char *copy_string_from_array(StringArray arr, size_t index);

/**
 * Function to remove a string from a StringArray at a specified index.
 * This function shifts the elements left to fill the gap.
 *
 * @param arr The array of strings from which to remove.
 * @param index The index of the string to remove.
 * @param num_tokens Pointer to the size of the array (number of tokens).
 * @return char* The removed string (dynamically allocated).
 */
char *remove_index_from_array(StringArray arr, size_t index, size_t *num_tokens);

#endif /* STRING_METHODS_H_ */
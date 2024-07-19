#include "memory_management.h"

void cleanup_resources(CsvResources *resources) {
    if (resources->csv_lines) {
        for (size_t i = 0; i < resources->csv_lines_quantity; i++) {
            free(resources->csv_lines[i]);
        }
        free(resources->csv_lines);
    }

    if (resources->header_positions) {
        free_header_dict(resources->header_positions);
    }

    if (resources->filters_struct) {
        free_filters(resources->filters_struct, resources->filters_quantity);
    }
}

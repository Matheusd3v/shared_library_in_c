#ifndef CAPTURE_STDOUT_H_
#define CAPTURE_STDOUT_H_


typedef struct {
    const char *input;
    const char *headers_output;
    const char *filter;
} ProcessCsvArgs;

char* capture_stdout(void (*func)(const char*, const char*, const char*), 
                     ProcessCsvArgs *csv_args);

char* generate_unique_filename(const char* base);


#endif /* CAPTURE_STDOUT_H_ */
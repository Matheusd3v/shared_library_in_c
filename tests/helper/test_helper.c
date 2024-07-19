#include "../../libcsv.h"
#include <stdio.h>
#include <stdlib.h>
#include "test_helper.h"
#include <unistd.h> 
#include <fcntl.h>  
#include <time.h>
#include <sys/wait.h>

char* generate_unique_filename(const char* base) {
    char* filename = malloc(64); 
    if (!filename) {
        perror("Failed to allocate memory for filename");
        exit(EXIT_FAILURE);
    }

    // Get the current time
    time_t now = time(NULL);
    
    // Generate a random number
    int random_number = rand() % 10000; 

    // Create the unique filename
    snprintf(filename, 64, "tests/temp/%s_%ld_%04d.txt", base, now, random_number);
    
    return filename;
}


char* capture_stdout(void (*func)(const char*, const char*, const char*), 
                     ProcessCsvArgs *csv_args) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return NULL;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return NULL;
    }

    if (pid == 0) { // Child process
        // Close read end
        close(pipefd[0]);

        // Redirect stdout to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO); // Redirect stderr as well

        // Call the function
        func(csv_args->input, csv_args->headers_output, csv_args->filter);

        // Close the write end and exit
        close(pipefd[1]);
        exit(0);
    } else { // Parent process
        // Close write end
        close(pipefd[1]);

        // Read output from the pipe
        char *output = malloc(1024); // Initial allocation
        ssize_t bytesRead = read(pipefd[0], output, 1024);
        if (bytesRead > 0) {
            output[bytesRead] = '\0'; // Null terminate
        } else {
            free(output);
            output = NULL;
        }

        // Wait for child process to finish
        wait(NULL);
        close(pipefd[0]);
        return output;
    }
}


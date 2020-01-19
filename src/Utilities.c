/// @file Utilities.c

#include <stdio.h>
#include <string.h>
#include "Utilities.h"

/// Allocates memory with passed size, exits the program on failure.
/// @param size
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);

    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}
#include <stdio.h>
#include <stdlib.h>

#define FAIL_ARGS __LINE__, __func__

// Prints the line and function that called. WILL EXIT PROGRAM
void fail_alloc(int LINE, const char *func)
{
    fprintf(
        stderr, 
        "Failed to allocate memory: >> %s():%d <<\n",
        func,
        LINE
    );
    exit(EXIT_FAILURE);
}

// Prints the line and function that called. Will free(p), then EXIT PROGRAM
void fail_realloc(void *p, int LINE, const char *func)
{
    free(p);
    fail_alloc(LINE, func);
}
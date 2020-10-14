#ifndef ALLOCERR_H
#define ALLOCERR_H

#include <stdio.h>
#include <stdlib.h>

#define FAIL_ARGS __LINE__, __func__

void fail_alloc(int LINE, const char *func);
void fail_realloc(void *p, int LINE, const char *func);

#endif

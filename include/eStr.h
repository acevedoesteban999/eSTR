#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define DEFAULT_OPTIMIZE_LEN 256

typedef struct {
    char *data;     
    size_t length;  
} eStr;

extern size_t OPTIMIZE_LEN;

bool estr_copy(eStr *str, const char *text);

bool estr_append_str(eStr *str, bool is_optimized_for_memory , const char *text);

bool estr_append_format(eStr *str,bool is_optimized_for_memory,const char *format, ...);

void estr_free(eStr *str);

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct {
    char *data;     
    size_t length;  
} eStr;

void estr_init(eStr *str);

bool estr_copy(eStr *str, const char *text);

bool estr_append_str(eStr *str, const char *text);

bool estr_append_format(eStr *str, const char *format, ...);

void estr_free(eStr *str);

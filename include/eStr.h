#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *data;     
    size_t length;  
} eStr;

void estr_init(eStr *str);

bool estr_copy(eStr *str, const char *text);

bool estr_append(eStr *str, const char *text);

void estr_free(eStr *str);

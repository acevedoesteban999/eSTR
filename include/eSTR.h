#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define DEFAULT_OPTIMIZE_LEN 256

//Example: 
//  eStr str;
//  ESTR_COPY_FORMAT(&str,"%i",100);
#define ESTR_COPY_FORMAT(str_addr, format, ...) \
    do { \
        estr_free(str_addr); \
        estr_append_format(str_addr, true, format, __VA_ARGS__); \
    } while (0)

typedef struct {
    char * ptr_char;    
    size_t length; 
    size_t capacity;
} eStr;

extern size_t OPTIMIZE_LEN;

bool estr_copy_str(eStr *str, const char *text);

bool estr_append_str(eStr *str, bool is_optimized_for_memory , const char *text);

bool estr_append_format(eStr *str,bool is_optimized_for_memory,const char *format, ...);

void estr_init(eStr *str);

void estr_free(eStr *str);

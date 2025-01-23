#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define DEFAULT_OPTIMIZE_LEN 256


#define ESTR_MULTIPLE_INIT(...) \
    do { \
        eSTR* strs[] = { __VA_ARGS__ }; \
        for (size_t i = 0; i < sizeof(strs) / sizeof(strs[0]); i++) { \
            estr_init(strs[i]); \
        } \
    } while (0)

//Example: 
//  eSTR str;
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
} eSTR;

extern size_t OPTIMIZE_LEN;

bool estr_literal_copy_str(eSTR * str, const char * text, unsigned len);

bool estr_copy_str(eSTR *str, const char *text);

bool estr_append_literal_str(eSTR * str, bool is_optimized_for_memory, const char * text, unsigned len);

bool estr_prepare_str(eSTR *str, size_t capacity);

bool estr_append_str(eSTR *str, bool is_optimized_for_memory , const char *text);

bool estr_append_format(eSTR *str,bool is_optimized_for_memory,const char *format, ...);

void estr_init(eSTR *str);

void estr_clear(eSTR *str);

void estr_free(eSTR *str);

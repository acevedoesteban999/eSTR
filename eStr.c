#include "eStr.h"

size_t OPTIMIZE_LEN = DEFAULT_OPTIMIZE_LEN;

typedef struct {
    char *data;    
    size_t length; 
    size_t capacity;
} eStr;


void estr_free(eStr *str) {
    if (str->data != NULL) {
        free(str->data); 
        str->data = NULL;
    }
    str->length = 0;
    str->capacity = 0;
}

bool estr_copy(eStr *str, const char *text) {
    estr_free(str);
    return estr_append_str(str,true, text);
}

bool estr_append_str(eStr *str, bool is_optimized_for_memory, const char *text ) {
    size_t text_len = strlen(text);
    size_t new_len = str->length + text_len;

    if (new_len + 1 > str->capacity) {

        size_t new_capacity = new_len + ( is_optimized_for_memory ? 0 : OPTIMIZE_LEN ) + 1;
        
        char *new_data = realloc(str->data, new_capacity); 
        if (!new_data) {
            return false; 
        }

        str->data = new_data;
        str->capacity = new_capacity;
    }

    memcpy(str->data + str->length, text, text_len + 1); 
    str->length = new_len;
    return true;
}

bool estr_append_format(eStr *str,bool is_optimized_for_memory, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int size = vsnprintf(NULL, 0, format, args);
    if (size < 0) {
        va_end(args);
        return false;
    }

    char *buff = (char *)malloc(size + 1); 
    if (!buff) {
        va_end(args);
        return false; 
    }

    vsnprintf(buff, size + 1, format, args);
    va_end(args);
    
    bool res = estr_append_str(str, is_optimized_for_memory, buff);
    free(buff);
    return res;
}
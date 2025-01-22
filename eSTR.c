#include "eSTR.h"


size_t OPTIMIZE_LEN = DEFAULT_OPTIMIZE_LEN;

void estr_init(eSTR *str){
    str->ptr_char = NULL;
    str->length = 0;
    str->capacity = 0;
}

void estr_free(eSTR *str) {
    if (str->ptr_char != NULL) {
        free(str->ptr_char); 
        str->ptr_char = NULL;
    }
    str->length = 0;
    str->capacity = 0;
}

bool estr_copy_str(eSTR *str, const char *text) {
    estr_free(str);
    return estr_append_str(str,true, text);
}

bool estr_append_str(eSTR *str, bool is_optimized_for_memory, const char *text ) {
    size_t text_len = strlen(text);
    size_t new_len = str->length + text_len;

    if (new_len + 1 > str->capacity) {

        size_t new_capacity = new_len + ( is_optimized_for_memory ? 0 : OPTIMIZE_LEN ) + 1;
        
        char *new_ptr_char = realloc(str->ptr_char, new_capacity); 
        if (!new_ptr_char) 
            return false; 

        str->ptr_char = new_ptr_char;
        str->capacity = new_capacity;
    }

    memcpy(str->ptr_char + str->length, text, text_len + 1); 
    str->length = new_len;
    return true;
}

bool estr_append_format(eSTR *str,bool is_optimized_for_memory, const char *format, ...) {
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

bool estr_prepare_str(eSTR *str, size_t capacity) {
    estr_free(str);
    
    char *new_ptr_char = malloc(capacity);
    if (!new_ptr_char)
        return false;

    str->ptr_char = new_ptr_char;
    str->capacity = capacity;
    str->length = 0;
    str->ptr_char[0] = '\0';
    
    return true;
}

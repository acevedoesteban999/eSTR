#include "eStr.h"

typedef struct {
    char *data;     
    size_t length;  
} eStr;

void estr_init(eStr *str) {
    str->data = NULL;
    str->length = 0;
}


bool estr_copy(eStr *str, const char *text) {
    estr_free(str);
    estr_append(str,text);
}

bool estr_append(eStr *str, const char *text) {
    size_t text_len = strlen(text);
    size_t new_len = str->length + text_len;

    char *new_data = realloc(str->data, new_len + 1); 
    if (!new_data) {
        return false; 
    }

    memcpy(new_data + str->length, text, text_len + 1);
    str->data = new_data;
    str->length = new_len;
    return true;
}

void estr_free(eStr *str) {
    if (str->data != NULL) {
        free(str->data); 
        str->data = NULL;
    }
    str->length = 0;
}


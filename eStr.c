#include "eStr.h"


void estr_init(eStr *str) {
    str->data = NULL;
    str->length = 0;
}

bool estr_copy(eStr *str, const char *text) {
    estr_free(str);
    return estr_append_str(str,text);
}

bool estr_append_str(eStr *str, const char *text) {
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

bool estr_append_format(eStr *str, const char *format, ...) {
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

    bool res = estr_append_format(str, buff);

    free(buff);

    return res;
}

void estr_free(eStr *str) {
    if (str->data != NULL) {
        free(str->data); 
        str->data = NULL;
    }
    str->length = 0;
}


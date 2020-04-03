#include <string.h>

// https://stackoverflow.com/a/37134815
char* strdup(const char* s1)
{
    char* str;
    size_t size = strlen(s1) + 1;
    
    str = malloc(size);
    if (str) {
        memcpy(str, s1, size);
    }
    return str;
}
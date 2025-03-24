#ifndef __STDC_STRING_H
#define __STDC_STRING_H

typedef unsigned long long size_t;

void* memcpy(void* dest, const void* src, size_t n) {
    for (int i = 0; i < n; ++i) {
        ((char*)dest)[i] = ((char*)src)[i];
    }
    return dest;
}

int strlen(char* s) {
    int i = 0;
    for (;;) {
        if (s[i] == '\0') {
            return i;
        }
        ++i;
    }
}

#endif
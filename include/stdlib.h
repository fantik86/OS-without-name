#ifndef __STDC_STDLIB_H
#define __STDC_STDLIB_H

#include <stddef.h>
#include <string.h>
#include <stdint.h>

void reverse(char s[])
{
    int i, j;
    char c;
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char* itoa(int n)
{
    int i, sign;
    char* s;
    if ((sign = n) < 0)
        n = -n;
        i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return s;
}

#endif

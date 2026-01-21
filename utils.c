#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/*
 * Unlimited input helpers:
 * - getString reads a full line (any length), returns heap-allocated string without '\n'
 * - getInt uses getString + atoi; frees the string.
 */

char* getString(const char* prompt) {
    if (prompt) printf("%s", prompt);

    int cap = 32;
    int len = 0;
    char* buf = (char*)malloc(cap);
    if (!buf) return NULL;

    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (len + 1 >= cap) {
            cap *= 2;
            char* nb = (char*)realloc(buf, cap);
            if (!nb) {
                free(buf);
                return NULL;
            }
            buf = nb;
        }
        buf[len++] = (char)ch;
    }
    buf[len] = '\0';

    /* shrink (optional) */
    char* out = (char*)realloc(buf, len + 1);
    return out ? out : buf;
}

int getInt(const char* prompt) {
    char* s = getString(prompt);
    if (!s) return 0;
    int v = atoi(s);
    free(s);
    return v;
}

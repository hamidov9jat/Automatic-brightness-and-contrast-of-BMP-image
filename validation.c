//
// Created by Nijat Hamidov and German Komarov on 5/21/2022.
//

#include "validation.h"

bool isBpm(char *s) {
    int ret = 0;

    if (s != NULL)
    {
        size_t size = strlen(s);

        if (size >= 4 &&
            s[size-4] == '.' &&
            s[size-3] == 'b' &&
            s[size-2] == 'm' &&
            s[size-1] == 'p')
        {
            ret = 1;
        }
    }

    return ret;
}
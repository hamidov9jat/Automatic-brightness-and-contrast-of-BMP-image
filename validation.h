//
// Created by Nijat Hamidov and German Komarov on 5/21/2022.
//

#ifndef DSA_PROJECT_VALIDATION_H
#define DSA_PROJECT_VALIDATION_H

#include <stdbool.h>
#include <string.h>

bool isBpm(char *str) {
    char *suffix = ".bpm";
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

#endif //DSA_PROJECT_VALIDATION_H

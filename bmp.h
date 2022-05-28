//
// Created by User on 5/28/2022.
//

#ifndef DSA_PROJECT_BMP_H
#define DSA_PROJECT_BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "stdlib.h"
#endif //DSA_PROJECT_BMP_H

struct BITMAP_HEADER {
    uint_fast8_t header_field[2]; // for 'B' and 'M'
    uint_fast32_t header_size; // size of the bmp header
    uint_fast32_t garbage; // two 2 bytes that are not necessary for us
    uint_fast32_t image_offset; // starting address of the byte where the bitmap image starts
} __attribute__((packed));

typedef struct BITMAP_HEADER sBITMAP_HEADER;

void open_bmp_file();
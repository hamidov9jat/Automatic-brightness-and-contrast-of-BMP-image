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

/* WARNING!!! Using C99 standard of C!
 * Using structure packing technique instead of
 * structure padding in order to eliminate wastage of
 * memory, although there will be wastage of CPU cycles
 * which is not primary concern in out cases.
 *
 * If the attribute((packed)) doesn't work,
 * instead you can include #pragma pack(1) directive
 * after #define DSA_PROJECT_BMP_H
 *
 * Concerning uint_fast32_t and other types:
 *  Fastest minimum-width integer types
 *  Not actually guaranteed to be fastest for all purposes
 *  Here we use the exact-width types for 8 and 16-bit ints.
 *
 * */


/*
 * This block of bytes is at the start of the file and is used to identify the file.
*/
struct BITMAP_HEADER {
    uint_fast8_t header_field[2]; // for 'B' and 'M'
    uint_fast32_t header_size; // size of the bmp header
    uint_fast32_t garbage; // two 2 bytes that are not necessary for us
    uint_fast32_t image_offset; // starting address of the byte where the bitmap image starts
} __attribute__((packed));

typedef struct BITMAP_HEADER sBITMAP_HEADER;

struct DIB_HEADER
{
    uint_fast32_t header_size;
    uint_fast32_t bmp_width;
    uint_fast32_t bmp_height;
    uint_fast16_t  color_planes; // note: 2 bytes
    uint_fast16_t bits_per_pixel; // note: 2 bytes
    uint_fast32_t compression_method;
    uint_fast32_t image_size;

    uint_fast32_t other[4]; // not used
};

void open_bmp_file(const char filename[]);
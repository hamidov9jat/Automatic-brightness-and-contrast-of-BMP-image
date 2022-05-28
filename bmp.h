//
// Created by User on 5/28/2022.
//

#ifndef DSA_PROJECT_BMP_H
#define DSA_PROJECT_BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>
#endif //DSA_PROJECT_BMP_H

/* WARNING!!! Using C99 standard of C!
 * Using structure packing technique instead of
 * structure padding in order to eliminate wastage of
 * memory, although there will be wastage of CPU cycles
 * which is not primary concern in out case.
 *
 * If the attribute((packed)) doesn't work,
 * instead you can include #pragma pack(1) directive
 * after #define DSA_PROJECT_BMP_H
 *
 * Concerning uint_fast32_t and other types:
 *  Fastest minimum-width integer types
 *  Not actually guaranteed to be fastest for all purposes
 *  Here we use the exact-width types for 8 and 16-bit ints.
 *  Basically, in comparison with uint_t, uint_fast32_t
 *  will try to take 4 bytes on someone's machine.
 * */


/*
 * This block of bytes is at the start of the file and is used to identify the file.
*/
struct BITMAP_HEADER {
    uint_fast8_t header_field[2]; // for 'B' and 'M'
    uint_fast32_t file_size; // size of the bmp file
    uint_fast32_t garbage; // two 2 bytes == 4 bytes that are not necessary for us
    uint_fast32_t image_offset; // starting address of the byte where the bitmap image starts
} __attribute__((packed));

typedef struct BITMAP_HEADER stBITMAP_HEADER;


/*
 * This block of bytes tells the application detailed information about the image,
 * which will be used to display the image on the screen.
 * The block also matches the header used internally by Windows and OS/2.
 */
struct DIB_HEADER
{
    uint_fast32_t header_size; // in bytes
    uint_fast32_t bmp_width;
    uint_fast32_t bmp_height;
    uint_fast16_t  color_planes; // note: 2 bytes
    uint_fast16_t bits_per_pixel; // note: 2 bytes
    uint_fast32_t compression_method_type; // and int indicating compression method (check wikipedia_
    uint_fast32_t image_size;

    uint_fast32_t additional[4]; // not used
//    uint_fast32_t compression_method[6]; // not used in code
} __attribute__((packed));

typedef struct DIB_HEADER stDIB_HEADER;

/*
 * The 32-bit per pixel (32bpp) format supports 4,294,967,296
 * distinct colors and stores 1 pixel per 4-byte DWORD.
 * Each DWORD can define the alpha, red, green and blue samples of the pixel.
 * */
struct RGB
{
    uint_fast8_t alpha;
    uint_fast8_t red;
    uint_fast8_t green;
    uint_fast8_t blue;
} __attribute__((packed));

typedef struct RGB stRGB;

/*
 * Bmp image will be a 2D array where each entry will be an rgb structure.
 * ptr_to_rgb_row[i] is a 1D array (a ith row) in the image
 * Each row will contain pointers to RGB structure.
 * Also store image width and height
*/
struct Image
{
    uint_fast32_t width;
    uint_fast32_t height;
    stRGB* *ptr_to_rgb_row; // 2D array of  the rgb structure
} __attribute__((packed));

typedef struct Image stImage;

struct BITMAP_FILE
{
    stBITMAP_HEADER bmp_header;
    uint_fast8_t *uneccessary;
    stDIB_HEADER dib_header;
    stImage pixel_array;
} __attribute__((packed));

typedef struct BITMAP_FILE stBitMapFile;

stImage read_bmp_image(FILE *file_pointer, uint_fast32_t width, uint_fast32_t height, uint_fast16_t bits_per_pixel,
                       uint_fast32_t bytes_to_read, uint_fast32_t number_of_rgb);
void create_bmp_image(stBITMAP_HEADER const *bmp_header, stDIB_HEADER const *dib_header, stImage const *bmp_image);
void free_bmp_image(stImage *bmp_image);
stBitMapFile read_bmp_file(stBitMapFile *ptr_to_bmp, FILE *file_ptr);
void open_bmp_file(const char filename[]);
uint32_t get_intensity(stRGB pixel);
void change_contrast(stRGB *ptr_pixel, float factor);
void auto_adjusting(stBitMapFile *bitMapFile);

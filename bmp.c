//
// Created by User on 5/28/2022.
//

#include "bmp.h"

stImage read_bmp_image(FILE *file_pointer, uint_fast32_t width, uint_fast32_t height, uint_fast16_t bits_per_pixel) {

    stImage bmp_image;
    bmp_image.width = width;
    bmp_image.height = height;

    // create 1D array each element of which will be a pointer to another 1D array of rgb structure pointers
    bmp_image.ptr_to_rgb_row = (stRGB **) malloc(height * sizeof(stRGB *)); // array of rows

    // In order to take into account padding in the bmp file we read appropriate number of bytes
    // from the file (specified in wikipedia by a formula)
    uint_fast32_t bytes_to_read = (uint_fast32_t) ( ceil((bits_per_pixel * width)) / 32 ) * 4;

    /*
    printf("Bytes to read %u\n", bytes_to_read);
    */

    // number of rgb structures in each row (integral division is used)
    uint_fast32_t number_of_rgb = bytes_to_read / sizeof(stRGB);

    /*
    printf("Size of rgb structure %u\n", sizeof(stRGB));
    printf("number of Rgb: %u\n", number_of_rgb);
    */

    // read image from bottom (i.e. i = height-1) to top
    int i;
    for (i = height - 1; i >= 0; i--) {
        // create 1D array on ith row
        bmp_image.ptr_to_rgb_row[i] = (stRGB *) malloc(number_of_rgb * sizeof(stRGB));

        // fill ith row (from bottom) from the file
        fread(bmp_image.ptr_to_rgb_row[i], 1, bytes_to_read, file_pointer);
    }

    return bmp_image;
}

void free_bmp_image(stImage bmp_image) {
    int i;
    for (i = bmp_image.height - 1; i >= 0; i--) {
        free(bmp_image.ptr_to_rgb_row[i]); // free ith row in bmp_image
    }

    free(bmp_image.ptr_to_rgb_row); // free array of rows
}

void open_bmp_file(const char filename[]) {
    FILE *file_pointer = fopen(filename, "rb");

    printf("%s\n", filename);
    if (file_pointer == NULL) {
        printf("%s\n", strerror(errno));
        exit(2);
    }

    stBITMAP_HEADER bmp_header;
    stDIB_HEADER dibHeader;

//    printf("size of bmp header %u\n", sizeof(bmp_header)); // checking the size of bmp header

    // read the bmp header
    fread(&bmp_header, sizeof(bmp_header), 1, file_pointer);

    // file pointer is on top of the dib_header since we are using structure packing
    fread(&dibHeader, sizeof(dibHeader), 1, file_pointer);

    // move file pointer to the first byte where the image starts
    fseek(file_pointer, bmp_header.image_offset, SEEK_SET); // from the begging + image_offset

    stImage bmp_image = read_bmp_image(file_pointer, dibHeader.bmp_width, dibHeader.bmp_height,
                                       dibHeader.bits_per_pixel);

    free_bmp_image(bmp_image);


    fclose(file_pointer);
}
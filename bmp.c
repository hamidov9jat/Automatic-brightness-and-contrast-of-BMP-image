//
// Created by User on 5/28/2022.
//

#include "bmp.h"

stImage read_bmp_image(FILE *file_pointer, uint_fast32_t width, uint_fast32_t height, stDIB_HEADER &) {

    stImage bmp_image;
    bmp_image.width = width;
    bmp_image.height = height;

    // create 1D array each element of which will be a pointer to another 1D array of rgb stucture pointers
    bmp_image.ptr_to_rgb_row = (stRGB **) malloc(height * sizeof(stRGB *));



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



    fclose(file_pointer);
}
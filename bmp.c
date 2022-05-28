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
    uint_fast32_t bytes_to_read = (uint_fast32_t) (ceil((bits_per_pixel * width)) / 32) * 4;

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

    for (i = bytes_to_read / sizeof (stRGB); i>=0 ; i--) {
        printf("%x ", bmp_image.ptr_to_rgb_row[height - 1][i]);
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

void create_bmp_image(stBITMAP_HEADER bmp_header, stDIB_HEADER dib_header, stImage bmp_image) {
    FILE *write_file_pointer = fopen("new.bmp", "wb");
    if (write_file_pointer == NULL) {
        puts("Error while creating bmp image");
        printf("%s\n", strerror(errno));
        exit(errno);
    }

    // writing bmp_header and dib_header into file
    fwrite(&bmp_header, sizeof(bmp_header), 1, write_file_pointer);
    fwrite(&dib_header, sizeof(dib_header), 1, write_file_pointer);

    uint_fast32_t bytes_to_read = (uint_fast32_t) ( ceil((dib_header.bits_per_pixel * bmp_image.width))
                                                     / 32 ) * 4;

//    printf("%u\n", bmp_header.image_offset);
//    printf("%u\n", bmp_header.bmp_file_size);
//    printf("%u\n", dib_header.image_size);
//    printf("size of the bmp header %u\n", sizeof (bmp_header));

    uint_fast8_t padding = bytes_to_read % sizeof(stRGB);

//    uint_fast8_t one_byte = 0; // to add additional space
//    //file pointer already read dib header so we can add additional for color table and bitmask
//    fwrite(&one_byte, sizeof (uint_fast8_t), bmp_header.image_offset -
//                                    (sizeof (bmp_header) + dib_header.header_size), write_file_pointer);


    int i;
    for (i = bmp_image.height - 1; i >= 0; i--) {
        fwrite(bmp_image.ptr_to_rgb_row[i], sizeof (stRGB), bytes_to_read,write_file_pointer);
    }

    fclose(write_file_pointer);
}

void open_bmp_file(const char filename[]) {
    FILE *file_pointer = fopen(filename, "rb");

//    printf("%s\n", filename);
    if (file_pointer == NULL) {
        puts("Error while reading bmp image");
        printf("%s\n", strerror(errno));
        exit(errno);
    }

    stBITMAP_HEADER bmp_header;
    stDIB_HEADER dibHeader;

//    printf("size of bmp header %u\n", sizeof(bmp_header)); // checking the size of bmp header

    // read the bmp header
    fread(&bmp_header, sizeof(bmp_header), 1, file_pointer);

    // file pointer is on top of the dib_header since we are using structure packing
    fread(&dibHeader, sizeof(dibHeader), 1, file_pointer);


    printf("header size %u\n", dibHeader.header_size);
    printf("width size %u\n", dibHeader.bmp_width);
    printf("height size %u\n", dibHeader.bmp_height);
    printf("Image size %u\n", dibHeader.image_size);
    printf("Image size %u\n", dibHeader.image_size);
    puts("--------------");
    printf("header size %x\n", dibHeader.header_size);
    printf("width size %x\n", dibHeader.bmp_width);
    printf("height size %x\n", dibHeader.bmp_height);
    printf("Image size %x\n", dibHeader.image_size);
//    printf("%x\n", dibHeader.other[0]);
//    printf("%x\n", dibHeader.other[1]);
//    printf("%x\n", dibHeader.other[2]);
//    printf("%x\n", dibHeader.other[3]);

    // move file pointer to the first byte where the image starts
    fseek(file_pointer, bmp_header.image_offset, SEEK_SET); // from the begging + image_offset

    stImage bmp_image = read_bmp_image(file_pointer, dibHeader.bmp_width, dibHeader.bmp_height,
                                       dibHeader.bits_per_pixel);

    create_bmp_image(bmp_header, dibHeader, bmp_image);

    free_bmp_image(bmp_image);
    fclose(file_pointer);
}
//
// Created by User on 5/28/2022.
//

#include "bmp.h"

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

    fread(&bmp_header, sizeof(bmp_header), 1, file_pointer);
    /*
    printf("%c%c field\n", bmp_header.header_field[0], bmp_header.header_field[1]);
    printf("size in bytes %d\n", bmp_header.header_size);
    printf("Offset: %d\n", bmp_header.image_offset);
*/


    fclose(file_pointer);
}
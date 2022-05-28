//
// Created by User on 5/28/2022.
//

#include "bmp.h"

void open_bmp_file() {
    FILE *file_pointer = fopen("example.bmp", "rb");

    if (file_pointer == NULL) {
        puts("Error while opening the file");
        exit(1);
    }

    sBITMAP_HEADER bmp_header;

    printf("size of bmp header %u\n", sizeof(bmp_header));

    fclose(file_pointer);
}
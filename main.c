//
// Created by Nijat Hamidov and German Komarov on 5/21/2022.
//

#include "bmp.h"

int main(void){
//    printf("Hello World!\n");
//    printf("%u\n", sizeof(uint_fast32_t));

    FILE *file_pointer = fopen64("example.bmp", "rb");

    if (file_pointer == NULL) {
        puts("Error while opening the file");
        printf("%d\n", errno);
        printf("%s\n", strerror(errno));
        exit(1);
    }


    fclose(file_pointer);

    return 0;
}
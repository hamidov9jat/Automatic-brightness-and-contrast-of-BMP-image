//
// Created by Nijat Hamidov and German Komarov on 5/21/2022.
//

#include "bmp.h"

bool isBmp(char *s);

int main(int argc, char **argv) {

//    open_bmp_file("C:\\Users\\User\\Documents\\Other\\dsa L2\\Automatic-brightness-and-contrast-of-BMP-image\\sampleview.bmp");

    printf("%d\n", argc);
    printf("last character is %d\n", argv[1][5]);
//    printf("%s\n", argv[1]);
    printf("%d\n", strlen(argv[1]) );
    printf("is bmp %d\n", isBmp(argv[1]));


    return 0;
}

bool isBmp(char *s) {
    int ret = 0;

    if (s != NULL) {
        size_t size = strlen(s);

        if (size > 4 &&
            s[size - 4] == '.' &&
            s[size - 3] == 'b' &&
            s[size - 2] == 'm' &&
            s[size - 1] == 'p') {
            ret = 1;
        }
    }

    return ret;
}

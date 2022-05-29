//
// Created by Герман Комаров on 29.05.22.
//

#include "helper.h"

#include <stdio.h>

void help() {
    printf("Your input must be in format : \n");
    printf("./main file1.bmp > file2.bmp\n");
    printf("./main file1.bmp -o file2.bmp\n");
    printf("(If you are on Windows, please use double quotes around file names)\n");
}
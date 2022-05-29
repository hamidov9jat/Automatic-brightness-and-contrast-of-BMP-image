//
// Created by Nijat Hamidov and German Komarov on 5/21/2022.
//

#include "bmp.h"
#include "validation.h"

int main(int argc, char **argv){


    printf("res : %d\n", isBpm("help.bmp"));
    printf("res : %d\n", isBpm("help.png"));


    return 0;
}
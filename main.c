//
// Created by Nijat Hamidov and German Komarov on 5/21/2022.
//

#include "bmp.h"
#include "helper_functions.h"

int main(int argc, char **argv) {


    validate_run(argc, argv);

    process_bmp_file(argv[1], argv[3]);


    return 0;
}



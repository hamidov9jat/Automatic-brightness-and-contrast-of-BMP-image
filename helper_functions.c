//
// Created by User on 5/29/2022.
//

#include "helper_functions.h"

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


void helper() {
    printf("\nYour input must be in format : \n");
    printf("./main file1.bmp > file2.bmp\nOr like this: ");
    printf("./main file1.bmp -o file2.bmp\n");
    printf("(If you are on Windows, please use double quotes around file names)\n");
    printf("Use: ./main -h for help\n\n");
}

void validate_run(int_fast32_t argc, char **argv) {

    if (argc < 2 || argc > 4 || argc == 3) {
        puts("Invalid number of arguments");
        helper();
        exit(1);
    }
    else if (argc == 4) {

        argc--;
        argv++;
    }

    int opt;
    while ((opt = getopt(argc, argv, "o:h")) != -1) {
        switch (opt) {
            case 'o':

                if ((argc + 1) != 4 || !isBmp(argv[argc - 3]) || !isBmp(argv[argc - 1])) {
                    puts("Please specify correct .bmp file");
                    exit(1);
                }
                break;

            case 'h':
                helper();
                exit(0);
                break;
            default:
                puts("Default");
                helper();
        }
/*

        // check for the output filename
        if (optind != argc - 1) {
            puts("Provide an output filename");
            exit(1);
        }
*/

    }
}
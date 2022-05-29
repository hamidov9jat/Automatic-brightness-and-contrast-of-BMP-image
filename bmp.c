//
// Created by User on 5/28/2022.
//

#include "bmp.h"


stImage read_bmp_image(FILE *file_pointer, uint_fast32_t width, uint_fast32_t height,
                       uint_fast32_t bytes_to_read, uint_fast32_t number_of_rgb) {

    stImage bmp_image;
    bmp_image.width = width;
    bmp_image.height = height;

    // create 1D array each element of which will be a pointer to another 1D array of rgb structure pointers
    bmp_image.ptr_to_rgb_row = (stRGB **) malloc(height * sizeof(stRGB *)); // array of rows




    // read image from bottom (i.e. i = height-1) to top
    int32_t i;
    for (i = height - 1; i >= 0; i--) {
        // create 1D array on ith row
        bmp_image.ptr_to_rgb_row[i] = (stRGB *) malloc(number_of_rgb * sizeof(stRGB));

        // fill ith row (from bottom) from the file
        fread(bmp_image.ptr_to_rgb_row[i], 1, bytes_to_read, file_pointer);
    }

#ifdef CHECK
    for (i = 0; i<number_of_rgb ; i++) {
        stRGB pixel = bmp_image.ptr_to_rgb_row[height - 1][i];
        printf("Alpha:%d,Red:%d,Green:%d,Blue:%d\n", pixel.alpha, pixel.red, pixel.green, pixel.blue);
    }*/
#endif

    return bmp_image;
}

void free_bmp_image(stImage *bmp_image) {
    int32_t i;
    for (i = bmp_image->height - 1; i >= 0; i--) {
        free((bmp_image->ptr_to_rgb_row)[i]); // free ith row in bmp_image
    }

    free(bmp_image->ptr_to_rgb_row); // free array of rows
}

void create_bmp_image(const stBitMapFile *const bmpfile) {
    FILE *write_file_pointer = fopen("new_image.bmp", "wb");
    if (write_file_pointer == NULL) {
        puts("Error while creating bmp image");
        printf("%s\n", strerror(errno));
        exit(errno);
    }

    // writing bmp_header and dib_header into file and if necessary additional space in between dib and pixel array
    fwrite(&(bmpfile->bmp_header), sizeof(bmpfile->bmp_header), 1, write_file_pointer);
    fwrite(&(bmpfile->dib_header), sizeof(bmpfile->dib_header), 1, write_file_pointer);
    if (bmpfile->space_between_dib_and_pixel_array > 0) {
        fwrite(bmpfile->unnecessary, sizeof(uint_fast8_t), bmpfile->space_between_dib_and_pixel_array,
               write_file_pointer);
    }


    uint_fast32_t bytes_to_read =
            (uint_fast32_t) (ceil((bmpfile->dib_header.bits_per_pixel * bmpfile->dib_header.bmp_width))
                             / 32) * 4;
    uint_fast32_t number_of_rgb = bytes_to_read / sizeof(stRGB);
    uint_fast8_t padding_size = bytes_to_read % sizeof(stRGB);
#ifdef CHECK
    printf("While writing unecessary is %u %x\n", (bmpfile->unnecessary)[1], (bmpfile->unnecessary)[1]);
    puts("------------Inside create----------");
    printf("bytes_to_read %u\n", bytes_to_read);
    printf("number_of_rgb %u\n", number_of_rgb);
    printf("padding_size %d\n", padding_size);
    printf("space_between_dib_image %d\n", bmpfile->space_between_dib_and_pixel_array);
    puts("-----------End create-----------------");
#endif

    int32_t i;
    if (padding_size == 0) {
        for (i = bmpfile->dib_header.bmp_height - 1; i >= 0; i--) {
            // write number_of_rgb structures to the file
            fwrite(bmpfile->pixel_array.ptr_to_rgb_row[i], sizeof(stRGB), number_of_rgb, write_file_pointer);
        }
    } else { // take into account padding
        uint_fast8_t padding[padding_size];// padding number of zeros
        for (i = 0; i < padding_size; i++) {
            padding[i] = 0;
        }

        for (i = bmpfile->dib_header.bmp_height - 1; i >= 0; i--) {

            // write number_of_rgb structures to the file and add necessary paddin
            fwrite(bmpfile->pixel_array.ptr_to_rgb_row[i], sizeof(stRGB), number_of_rgb, write_file_pointer);
            fwrite(padding, sizeof(uint_fast8_t), padding_size, write_file_pointer);
        }
    }

    fclose(write_file_pointer);
}

stBitMapFile read_bmp_file(stBitMapFile *ptr_to_bmp, FILE *file_ptr) {

    // read the bmp header
    fread(&(ptr_to_bmp->bmp_header), sizeof(ptr_to_bmp->bmp_header), 1, file_ptr);

    // file pointer is on top of the dib_header since we are using structure packing
    // read  54 bytes (sizeof dib header) after reading bmp header
    fread(&(ptr_to_bmp->dib_header), sizeof(ptr_to_bmp->dib_header), 1, file_ptr);

#ifdef CHECK
    puts("-----------In read bmp file---------------");
    printf("dec %c%c and %x %x hex ptr_to_bmp->bmp_header.header_fields\n", ptr_to_bmp->bmp_header.header_field[0],
           ptr_to_bmp->bmp_header.header_field[1],
           ptr_to_bmp->bmp_header.header_field, ptr_to_bmp->bmp_header.header_field + 1);
    printf("dec %u and %x hex ptr_to_bmp->bmp_header.file_size\n", ptr_to_bmp->bmp_header.file_size);
    printf("dec %u and %x hex ptr_to_bmp->bmp_header.garbage\n", ptr_to_bmp->bmp_header.garbage);
    printf("dec %u and %x hex ptr_to_bmp->bmp_header.image_offset\n", ptr_to_bmp->bmp_header.image_offset);
    printf("%u sizeof(ptr_to_bmp->bmp_header)\n", sizeof(ptr_to_bmp->bmp_header));

    puts("---------------- --------------------------");
    printf("dec %u and %x hex ptr_to_bmp->dib_header.header_size\n", ptr_to_bmp->dib_header.header_size);
    printf("dec %u and %x hex ptr_to_bmp->dib_header.bmp_width\n", ptr_to_bmp->dib_header.bmp_width);
    printf("dec %u and %x hex ptr_to_bmp->dib_header.bmp_height\n", ptr_to_bmp->dib_header.bmp_height);
    printf("dec %u and %x hex ptr_to_bmp->dib_header.color_planes\n", ptr_to_bmp->dib_header.color_planes);
    printf("dec %u and %x hex ptr_to_bmp->dib_header.bits_per_pixel\n", ptr_to_bmp->dib_header.bits_per_pixel);
    printf("dec %u and %x hex ptr_to_bmp->dib_header.compression_method_type\n",
           ptr_to_bmp->dib_header.compression_method_type);
    printf("dec %u and %x hex ptr_to_bmp->dib_header.image_size\n", ptr_to_bmp->dib_header.image_size);
    printf("%u sizeof(ptr_to_bmp->dib_header)\n", sizeof(ptr_to_bmp->dib_header));
    puts("------------------End------------------------");


    puts("------------Inside read bmp part 2----------");
    printf("bytes_to_read %u\n", bytes_to_read);
    printf("number_of_rgb %u\n", number_of_rgb);
    printf("padding_size %u\n", padding_size);
    printf("ptr_to_bmp->space_between_dib_and_pixel_array %d\n", ptr_to_bmp->space_between_dib_and_pixel_array);
    puts("-----------End read-----------------");

#endif

    // In order to take into account padding in the bmp file we read appropriate number of bytes
    // from the file (specified in wikipedia by a formula)
    uint_fast32_t bytes_to_read =
            (uint_fast32_t) (ceil((ptr_to_bmp->dib_header.bits_per_pixel * ptr_to_bmp->dib_header.bmp_width))
                             / 32) * 4;

    // number of rgb structures in each row (integral division is used)
    uint_fast32_t number_of_rgb = bytes_to_read / sizeof(stRGB);

    uint_fast8_t padding_size = bytes_to_read % sizeof(stRGB);
    ptr_to_bmp->space_between_dib_and_pixel_array =
            ptr_to_bmp->bmp_header.image_offset - (sizeof(ptr_to_bmp->bmp_header) + sizeof(ptr_to_bmp->dib_header));

    fseek(file_ptr, sizeof(ptr_to_bmp->bmp_header) + sizeof(ptr_to_bmp->dib_header), SEEK_SET);
    if (ptr_to_bmp->space_between_dib_and_pixel_array > 0) {
        ptr_to_bmp->unnecessary = (uint_fast8_t *) malloc(
                ptr_to_bmp->space_between_dib_and_pixel_array * sizeof(uint_fast8_t));
        fread(ptr_to_bmp->unnecessary, sizeof(uint_fast8_t), ptr_to_bmp->space_between_dib_and_pixel_array, file_ptr);
    }

    fseek(file_ptr, ptr_to_bmp->bmp_header.image_offset, SEEK_SET);
    ptr_to_bmp->pixel_array = read_bmp_image(file_ptr, ptr_to_bmp->dib_header.bmp_width,
                                             ptr_to_bmp->dib_header.bmp_height,
                                             bytes_to_read, number_of_rgb);

    return *ptr_to_bmp;

}

void open_bmp_file(const char filename[]) {
    FILE *file_pointer = fopen(filename, "rb");

    if (file_pointer == NULL) {
        puts("Error while reading bmp image");
        printf("%s\n", strerror(errno));
        exit(errno);
    }


    stBitMapFile bmp_file;
    bmp_file = read_bmp_file(&bmp_file, file_pointer);
    auto_adjusting(&bmp_file);
    create_bmp_image(&bmp_file);

    fseek(file_pointer, 0, SEEK_SET);

    free_bmp_image(&(bmp_file.pixel_array));
    free(bmp_file.unnecessary);
    fclose(file_pointer);
}

void auto_adjusting(stBitMapFile *bitMapFile) {

/*
     * Make intensities spread between 255*.95 and 255 * .25
*/
    uint_fast8_t red_min = (uint_fast8_t)(255*.97F);
    uint_fast8_t red_max = 0;
    //
    uint_fast8_t green_min = (uint_fast8_t)(255*.97F);
    uint_fast8_t green_max = 0;
    //
    uint_fast8_t blue_min = (uint_fast8_t)(255*.97F);
    uint_fast8_t blue_max = 0;

    /*
     * Find the lowes and highest intensities of each color
     * */


    int32_t i, j;
    uint32_t height = bitMapFile->dib_header.bmp_height,
            width = bitMapFile->dib_header.bmp_width;


    for (i = height - 1; i >= 0; i--) {
        for (j = 0; j < width; j++) {
            uint_fast8_t red = (bitMapFile->pixel_array).ptr_to_rgb_row[i][j].red,
                    green = (bitMapFile->pixel_array).ptr_to_rgb_row[i][j].green,
                    blue = (bitMapFile->pixel_array).ptr_to_rgb_row[i][j].blue;

            if (red_min > red) red_min = red;
            if (red_max < red) red_max = red;
            //
            if (green_min > green) green_min = green;
            if (green_max < green) green_max = green;
            //
            if (blue_min > blue) blue_min = blue;
            if (blue_max < blue) blue_max = blue;

        }
    }

    // calculate scaling factor max and min should be different
    // in order to prevent division by zeof
    float red_scale = 1.0F, green_scale = 1.0F, blue_scale = 1.0F;

    if (red_max > red_min) red_scale = 255.0F / (red_max - red_min);
    if (green_max > green_min) green_scale = 255.0F / (green_max - green_min);
    if (blue_max > blue_min) blue_scale = 255.0F / (blue_max - blue_min);

    // normalize pixels
    for (i = height - 1; i >= 0; i--) {
        for (j = 0; j < width; j++) {
            ((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].red) =
                    (uint_fast8_t) (red_scale * ((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].red - red_min));
            ((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].green) =
                    (uint_fast8_t) (green_scale * ((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].green - green_min));
            ((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].blue) =
                    (uint_fast8_t) (blue_scale * ((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].blue - blue_min));
            /*if (((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].red - red_min) < 0) printf("rA\n");
            if (((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].green - green_min) < 0) printf("gA\n");
            if (((bitMapFile->pixel_array).ptr_to_rgb_row[i][j].blue - blue_min) < 0)
                printf("bA%d %d\n",
                       (bitMapFile->pixel_array).ptr_to_rgb_row[i][j].blue, blue_min);
        */}
    }


}

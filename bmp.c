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

/* check
    for (i = 0; i<number_of_rgb ; i++) {
        stRGB pixel = bmp_image.ptr_to_rgb_row[height - 1][i];
        printf("Alpha:%d,Red:%d,Green:%d,Blue:%d\n", pixel.alpha, pixel.red, pixel.green, pixel.blue);
    }*/

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

    printf("While writing unecessary is %u %x\n", (bmpfile->unnecessary)[1], (bmpfile->unnecessary)[1]);

    uint_fast32_t bytes_to_read =
            (uint_fast32_t) (ceil((bmpfile->dib_header.bits_per_pixel * bmpfile->dib_header.bmp_width))
                             / 32) * 4;
    uint_fast32_t number_of_rgb = bytes_to_read / sizeof(stRGB);
    uint_fast8_t padding_size = bytes_to_read % sizeof(stRGB);

    puts("------------Inside create----------");
    printf("bytes_to_read %u\n", bytes_to_read);
    printf("number_of_rgb %u\n", number_of_rgb);
    printf("padding_size %d\n", padding_size);
    printf("space_between_dib_image %d\n", bmpfile->space_between_dib_and_pixel_array);
    puts("-----------End create-----------------");


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

    puts("------------Inside read bmp part 2----------");
    printf("bytes_to_read %u\n", bytes_to_read);
    printf("number_of_rgb %u\n", number_of_rgb);
    printf("padding_size %u\n", padding_size);
    printf("ptr_to_bmp->space_between_dib_and_pixel_array %d\n", ptr_to_bmp->space_between_dib_and_pixel_array);
    puts("-----------End read-----------------");

    fseek(file_ptr, sizeof (ptr_to_bmp->bmp_header) + sizeof (ptr_to_bmp->dib_header), SEEK_SET);
    if (ptr_to_bmp->space_between_dib_and_pixel_array > 0) {
        ptr_to_bmp->unnecessary = (uint_fast8_t *) malloc(ptr_to_bmp->space_between_dib_and_pixel_array * sizeof (uint_fast8_t));
        fread(ptr_to_bmp->unnecessary,sizeof (uint_fast8_t), ptr_to_bmp->space_between_dib_and_pixel_array, file_ptr);
    }

//    printf("sizeof(ptr_to_bmp->unnecessary): %u\n", sizeof(ptr_to_bmp->unnecessary));
//    printf("%u and %x hex is *(ptr_to_bmp->unnecessary + 2)\n", *(ptr_to_bmp->unnecessary + 17),
//           *(ptr_to_bmp->unnecessary + 17));

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
//    auto_adjusting(&bmp_file);
    create_bmp_image(&bmp_file);

    fseek(file_pointer, 0, SEEK_SET);

    free_bmp_image(&(bmp_file.pixel_array));
    free(bmp_file.unnecessary);
    fclose(file_pointer);
}

uint32_t get_intensity(stRGB pixel) {
    return (pixel.red + pixel.green + pixel.blue) / 3;
}

void change_contrast(stRGB *ptr_pixel, float factor) {
    ptr_pixel->red = ptr_pixel->red * factor; // implicit typecasting
    ptr_pixel->green = ptr_pixel->green * factor; // implicit typecasting
    ptr_pixel->blue = ptr_pixel->blue * factor; // implicit typecasting

}


void auto_adjusting(stBitMapFile *bitMapFile) {

/*
     * Find the max and min pixel intensities in the image
*/

    int32_t i, j;
    uint_fast32_t new_intensity = 1, current_intensity = 0;
    uint32_t height = bitMapFile->dib_header.bmp_height,
            width = bitMapFile->dib_header.bmp_width;
    uint32_t maxIntensity = 150, minIntensity = 10;


    for (i = height - 1; i >= 0; i--) {
        for (j = 0; j < width; j++) {
            current_intensity = get_intensity((bitMapFile->pixel_array.ptr_to_rgb_row)[i][j]);
            if (current_intensity > maxIntensity) {
                maxIntensity = current_intensity;
            }
            if (current_intensity < minIntensity) {
                minIntensity = current_intensity;
            }
        }
    }
    printf("Minimum pixel intensity: %u\n", minIntensity);
    printf("Maximum pixel intensity: %u\n", maxIntensity);

    float intensity_factor;
    for (i = height - 1; i >= 0; i--) {
        for (j = 0; j < width; j++) {
            current_intensity = get_intensity((bitMapFile->pixel_array.ptr_to_rgb_row)[i][j]);
            intensity_factor = (255.0F * ((current_intensity - minIntensity) /
                                               (maxIntensity - minIntensity)));
//            if (intensity_factor < 0 || intensity_factor > 255) printf("kak tak?");
            change_contrast((bitMapFile->pixel_array.ptr_to_rgb_row)[i] + j, intensity_factor);

        }
    }


}

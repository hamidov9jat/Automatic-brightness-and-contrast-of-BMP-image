//
// Created by User on 5/28/2022.
//

#include "bmp.h"

stImage read_bmp_image(FILE *file_pointer, uint_fast32_t width, uint_fast32_t height, uint_fast16_t bits_per_pixel) {

    stImage bmp_image;
    bmp_image.width = width;
    bmp_image.height = height;

    // create 1D array each element of which will be a pointer to another 1D array of rgb structure pointers
    bmp_image.ptr_to_rgb_row = (stRGB **) malloc(height * sizeof(stRGB *)); // array of rows

    // In order to take into account padding in the bmp file we read appropriate number of bytes
    // from the file (specified in wikipedia by a formula)
    uint_fast32_t bytes_to_read = (uint_fast32_t) (ceil((bits_per_pixel * width)) / 32) * 4;

    /*
    printf("Bytes to read %u\n", bytes_to_read);
    */

    // number of rgb structures in each row (integral division is used)
    uint_fast32_t number_of_rgb = bytes_to_read / sizeof(stRGB);
/*

    printf("Size of rgb structure %u\n", sizeof(stRGB));
    printf("number of Rgb: %u\n", number_of_rgb);
*/

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

void create_bmp_image(stBITMAP_HEADER const *bmp_header, stDIB_HEADER const *dib_header, stImage const *bmp_image) {
    FILE *write_file_pointer = fopen64("new.bmp",
                                     "wb");
    if (write_file_pointer == NULL) {
        puts("Error while creating bmp image");
        printf("%s\n", strerror(errno));
        exit(errno);
    }

    // writing bmp_header and dib_header into file
    fwrite(bmp_header, sizeof(*bmp_header), 1, write_file_pointer);
    fwrite(dib_header, sizeof(*dib_header), 1, write_file_pointer);
/*

    printf("IN create\n");
    printf("bmp_header.image_offset %u\n", bmp_header->image_offset);
    printf("bmp_header->file_size %u\n", bmp_header->file_size);
    printf("dib_header->image_size %u\n", dib_header->image_size);
    printf("dib_header->header_size %u\n", dib_header->header_size);

    printf("sizeof (bmp_header) %u\n", sizeof (*bmp_header));
    printf("sizeof (dib_header) %u\n", sizeof (*dib_header));
*/

    uint_fast32_t bytes_to_read = (uint_fast32_t) (ceil((dib_header->bits_per_pixel * bmp_image->width))
                                                   / 32) * 4;

    uint_fast32_t number_of_rgb = bytes_to_read / sizeof(stRGB);
    uint_fast8_t padding_size = bytes_to_read % sizeof(stRGB);
//    printf("padding_size %u\n", padding_size);

    int32_t space_between_dib_image = bmp_header->image_offset - (sizeof(*bmp_header) + sizeof (*dib_header));

//    printf("Space between %d\n", space_between_dib_image);

    // add zeros between part of dib header and pixel array
    if (space_between_dib_image > 0) {
        uint_fast8_t zeros[space_between_dib_image];
        for (uint_fast32_t i = 0; i < space_between_dib_image; i++) {
            zeros[i] = 0;
        }

        fwrite(zeros, sizeof (uint_fast8_t), space_between_dib_image, write_file_pointer);
    }



    int i;
    if (padding_size == 0) {
        for (i = bmp_image->height - 1; i >= 0; i--) {
            // write number_of_rgb structures to the file
            fwrite(bmp_image->ptr_to_rgb_row[i], sizeof(stRGB), number_of_rgb, write_file_pointer);
        }
    } else { // take into account padding
        uint_fast8_t padding[padding_size];// padding number of zeros
        for (i = 0; i < padding_size; i++) {
            padding[i] = 0;
        }

        for (i = bmp_image->height - 1; i >= 0; i--) {

            // write number_of_rgb structures to the file and add necessary paddin
            fwrite(bmp_image->ptr_to_rgb_row[i], sizeof(stRGB), number_of_rgb, write_file_pointer);
            fwrite(padding, sizeof(uint_fast8_t), padding_size, write_file_pointer);
        }
    }


    fclose(write_file_pointer);
}

void open_bmp_file(const char filename[]) {
    FILE *file_pointer = fopen(filename, "rb");

    if (file_pointer == NULL) {
        puts("Error while reading bmp image");
        printf("%s\n", strerror(errno));
        exit(errno);
    }

    stBITMAP_HEADER bmp_header;
    stDIB_HEADER dibHeader;

//    printf("size of bmp header %u\n", sizeof(bmp_header)); // checking the size of bmp header

    // read the bmp header
    fread(&bmp_header, sizeof(bmp_header), 1, file_pointer);

    // file pointer is on top of the dib_header since we are using structure packing
    fread(&dibHeader, sizeof(dibHeader), 1, file_pointer);

/*

    printf("header size %u\n", dibHeader.header_size);
    printf("width size %u\n", dibHeader.bmp_width);
    printf("height size %u\n", dibHeader.bmp_height);
    printf("Image size %u\n", dibHeader.image_size);
    printf("Compression method size %u\n", dibHeader.compression_method_type);
    printf("Image offset %x and %u in dec\n", bmp_header.image_offset, bmp_header.image_offset);

    puts("--------------");
    printf("header size %x\n", dibHeader.header_size);
    printf("width size %x\n", dibHeader.bmp_width);
    printf("height size %x\n", dibHeader.bmp_height);
    printf("Image size %x\n", dibHeader.image_size);
    printf("%u\n", dibHeader.additional[0]);
    printf("%u\n", dibHeader.additional[1]);
    printf("%u\n", dibHeader.additional[2]);
    printf("%u\n", dibHeader.additional[3]);
    puts("");
*/

    // move file pointer to the first byte where the image starts
    fseek(file_pointer, bmp_header.image_offset, SEEK_SET); // from the begging + image_offset

    stImage bmp_image = read_bmp_image(file_pointer, dibHeader.bmp_width, dibHeader.bmp_height,
                                       dibHeader.bits_per_pixel);

    auto_adjusting(&bmp_image);
//    create_bmp_image(&bmp_header, &dibHeader, &bmp_image);



    free_bmp_image(&bmp_image);
    fclose(file_pointer);
}

uint32_t get_intensity(stRGB pixel){
    return (pixel.red + pixel.green + pixel.blue) / 3;
}

void change_contrast(stRGB *ptr_pixel, float factor)
{
    ptr_pixel->red = ptr_pixel->red * factor; // implicit typecasting
    ptr_pixel->green = ptr_pixel->green * factor; // implicit typecasting
    ptr_pixel->blue = ptr_pixel->blue * factor; // implicit typecasting

}


void auto_adjusting(stImage *bmp_image)
{
    // Max and min intensities that the pixel can have
    uint_fast32_t maxIntensity= 155, minIntensity = 100;

    /*
     * Find the max and min pixel intensities in the image
     */

    int32_t i, j;
    uint_fast32_t new_intensity = 1, current_intensity = 0;
    for (i = bmp_image->height - 1;  i >= 0; i--) {
        for (j = 0; j < bmp_image->width; j++) {
            current_intensity = get_intensity((bmp_image->ptr_to_rgb_row)[i][j]);
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
    for (i = bmp_image->height - 1;  i >= 0; i--) {
        for (j = 0; j < bmp_image->width; j++) {
            current_intensity = get_intensity((bmp_image->ptr_to_rgb_row)[i][j]);
            intensity_factor = (float)(255 * ( (get_intensity((bmp_image->ptr_to_rgb_row)[i][j]) - minIntensity) /
                                    (maxIntensity - minIntensity)));
            if (intensity_factor < 0 || intensity_factor > 255) printf("kak tak?");
            change_contrast((bmp_image->ptr_to_rgb_row)[i]+j, intensity_factor);

        }
    }

}
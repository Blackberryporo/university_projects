#ifndef _IMAGE_ROTATION_C_
#define _IMAGE_ROTATION_C_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "image_rotation.h"

write_error_code_t save_image_bmp(FILE* out, struct image_t const* img)
{
    struct bmp_header_t header;
    size_t i, j;
    size_t rowsize = ((24*img->width +31) / 32) * 4;
    size_t pad = (img->width * sizeof(struct pixel_t) % 4) ? 4 - (img->width*sizeof(struct pixel_t) % 4) : 0;

    header.bfType = 0x4D42;
    header.bfileSize = sizeof(struct bmp_header_t) + rowsize * img->height;
    header.bfReserved = 0;
    header.bOffBits = 54;
    header.biSize = 40;

    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;

    fwrite(&header, sizeof(struct bmp_header_t), 1, out);
    if (ferror(out) || feof(out)) return WRITE_ERROR;
    fseek(out, 54, SEEK_SET);

    for(i = 0; i < img->height; ++i)
    {
        for(j = 0; j < img->width; ++j)
        {
            fwrite (&img->data[i * (img->width) + j], sizeof(struct pixel_t), 1, out);
            if (ferror(out) || feof(out)) return WRITE_ERROR;
        }

        fwrite("pad", pad, 1, out);
    }

    return WRITE_OK;
}

read_error_code_t read_from_bmp(FILE* in, struct image_t* const read, struct pixel_t* const pixel)
{
    uint32_t table_location;
    size_t i, j;
    size_t pad;

    fseek(in, 10, SEEK_SET);
    fread(&table_location, sizeof(uint32_t), 1, in);
    if (ferror(in) || feof(in)) return READ_INVALID_PIXEL_TABLE_LOCATION;
    fseek(in, 18, SEEK_SET);
    fread(&read->width, sizeof(uint32_t), 1, in);
    if (ferror(in) || feof(in)) return READ_INVALID_WIDTH;
    fread(&read->height, sizeof(uint32_t), 1, in);
    if (ferror(in) || feof(in)) return READ_INVALID_HEIGHT;

    read->data = malloc(sizeof(struct pixel_t)*read->width*read->height);
    pad = (read->width * sizeof(struct pixel_t) % 4) ? 4 - (read->width*sizeof(struct pixel_t) % 4) : 0;
    fseek(in, table_location, SEEK_SET);
    for(i = 0; i < read->height; ++i)
    {
        for(j = 0; j < read->width; ++j)
        {
            fread (&read->data[i * (read->width) + j], sizeof(struct pixel_t), 1, in);
            if (ferror(in) || feof(in)) return READ_INVALID_PIXEL;
        }
        fseek(in, pad, SEEK_CUR);
    }

    return READ_OK;
}

#endif

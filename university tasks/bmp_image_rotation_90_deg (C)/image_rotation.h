#ifndef _IMAGE_ROTATION_H_
#define _IMAGE_ROTATION_H_

#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
struct pixel_t {char b,g,r;};
#pragma pack(pop)

struct image_t {
    uint32_t width, height;
    struct pixel_t* data;
};

#pragma pack(push, 2)
struct bmp_header_t {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;

    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} ;
#pragma pack(pop)

typedef enum {
    READ_OK = 0,
    READ_INVALID_PIXEL_TABLE_LOCATION,
	READ_INVALID_PIXEL,
    READ_INVALID_WIDTH,
	READ_INVALID_HEIGHT,
	READ_INVALID_SIGNATURE
} read_error_code_t;

typedef enum {
    WRITE_OK = 0,
	WRITE_ERROR
} write_error_code_t;

struct image_t rotate(struct image_t const source, const char direction);

write_error_code_t save_image_bmp(FILE* out, struct image_t const* img);

read_error_code_t read_from_bmp(FILE* in, struct image_t* const read, struct pixel_t* const pixel);

#endif

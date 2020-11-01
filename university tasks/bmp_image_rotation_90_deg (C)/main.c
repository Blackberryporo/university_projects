#include "image_rotation.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

static int8_t get_file_name(char* file_name)
{
    char* newline;
    if (file_name == NULL)
    {
        return 1;
    }
    fgets(file_name, MAX_PATH, stdin);
    newline = strchr(file_name, '\n');
    if (newline != NULL)
    {
        *newline = '\0';
    }
    return 0;
}

static FILE* open_file(const char *name)
{
    FILE* image = fopen(name, "rb");
    return image;
}

static FILE* create_file()
{
    FILE* image = fopen("result.bmp", "wb");
    return image;
}

struct image_t rotate(struct image_t const source, const char direction)
{
    struct image_t new_image;
    size_t i, j;

    new_image.data = malloc(sizeof(struct pixel_t) * source.width * source.height);
    new_image.width = source.height;
    new_image.height = source.width;

    if (direction == '1')
    {
        for (i = 0; i < source.width; i++)
            for (j = 0; j < source.height; j++)
                new_image.data[i*source.height+j] = source.data[(source.height-(j+1))*source.width+i];
    }
    else if (direction == '2')
    {
        for (i = 0; i < source.width; i++)
            for (j = 0; j < source.height; j++)
                new_image.data[i*source.height+j] = source.data[j*source.width+source.width-(i+1)];
    }

    return new_image;
}

void check_read_error(read_error_code_t error)
{
    switch(error)
    {
        case READ_OK:
            printf("READ_OK\n");
            break;

        case READ_INVALID_SIGNATURE:
            printf("READ_INVALID_SIGNATURE\n");
            break;

        case READ_INVALID_PIXEL_TABLE_LOCATION:
            printf("READ_INVALID_PIXEL_TABLE_LOCATION\n");
            break;

        case READ_INVALID_PIXEL:
            printf("READ_INVALID_PIXEL\n");
            break;

        case READ_INVALID_WIDTH:
            printf("READ_INVALID_WIDTH\n");
            break;

        case READ_INVALID_HEIGHT:
            printf("READ_INVALID_HEIGHT\n");
            break;
    }
}

void check_write_error(write_error_code_t error)
{
    switch(error)
    {
        case WRITE_OK:
            printf("WRITE_OK\n");
            break;

        case WRITE_ERROR:
            printf("WRITE_ERROR\n");
            break;
    }
}

int main(int argc, char *argv[])
{
    FILE* image_file;
    FILE* new_image_file;
    struct image_t image_struct;
    struct image_t new_image;
    read_error_code_t read_error;
    write_error_code_t write_error;
    char file_name[MAX_PATH] = {0};
    char direction = '0';

    printf("Type the file name:\n");
    if (get_file_name(file_name) != 0)
    {
        printf("File name error.\n");
        exit(EXIT_FAILURE);
    }
    image_file = open_file(file_name);
    if (image_file == NULL)
    {
        printf("Cannot open the file!\n");
        exit(EXIT_FAILURE);
    }
    read_error = read_from_bmp(image_file, &image_struct, image_struct.data);
    check_read_error(read_error);
    new_image_file = create_file();
    if (new_image_file == NULL)
    {
        printf("Cannot create new file!\n");
        exit(EXIT_FAILURE);
    }

    while ((direction != '1') && (direction != '2'))
    {
        if (direction != '\n')
        {
            printf("Type 1 to rotate 90 deg left, type 2 to rotate 90 deg right\n");
        }
        direction = getchar();
        if ((direction == '1') || (direction == '2'))
        {
            new_image = rotate(image_struct, direction);
        }
    }
    write_error = save_image_bmp(new_image_file, &new_image);
    check_write_error(write_error);

    fclose(image_file);
    fclose(new_image_file);
    free(new_image.data);
    free(image_struct.data);

    return 0;
}

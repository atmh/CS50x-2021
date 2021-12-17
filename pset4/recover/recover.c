#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // variables
    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    char fileName[8];
    FILE *out_ptr = NULL;

    // argc must be 2, otherwise reject
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open input
    char *file = argv[1];
    FILE *in_ptr = fopen(file, "r");

    // if unable to open
    if (in_ptr == NULL)
    {
        printf("Error: cannot open %s\n", file);
        return 2;
    }

    while (fread(&buffer, BLOCK_SIZE, 1, in_ptr) == 1)
    {
        // new jpeg check
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if not first, close
            if (count != 0)
            {
                fclose(out_ptr);
            }

            // init
            sprintf(fileName, "%03i.jpg", count);
            out_ptr = fopen(fileName, "w");
            count++;
        }

        // if found
        if (count != 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, out_ptr);
        }
    }

    fclose(in_ptr);
    fclose(out_ptr);
}
#include "../include/utils.h"

// Extends the sign to a 16-bit number
// x: the number to be extended
// bit_count: the number of bits in the number = 5
// Immediate value (unsigned) in this vm is 5 bits long
// PC in this vm is 16 bits long
// Example:
// 00001 -> 1
// -1 in 5 bits is 1 1111, but the x will be -1 in 16 bits
// sign_extend(0x1F, 5) -> 0xFF
uint16_t sign_extend(uint16_t x, int bit_count)
{
    // Check if the sign bit is set
    // For 5 bits, the sign bit is the 4th bit
    // so right shift the number by 4 bits
    // and check if the 1st bit is set
    if ((x >> (bit_count - 1)) & 1)
    {
        // extend by setting all the bits to the left of the sign bit to 1
        // (Two's complement)
        x |= (0xFFFF << bit_count);
    }
    return x;
}

// Converts big endian to little endian
uint16_t swap16(uint16_t x)
{
    return (x << 8) | (x >> 8);
}

// Read the image file into memory
void read_image_file(FILE *file)
{
    // The origin tells us where in memory to place the image
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, file);
    origin = swap16(origin);

    // We know the maximum file size so we only need one fread
    uint16_t max_read = MAX_MEMORY - origin;
    uint16_t *p = memory + origin;
    size_t read = fread(p, sizeof(uint16_t), max_read, file);

    // Swap to little endian
    while (read-- > 0)
    {
        *p = swap16(*p);
        ++p;
    }
}

int read_image(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        return 0;
    }
    read_image_file(file);
    fclose(file);
    return 1;
}

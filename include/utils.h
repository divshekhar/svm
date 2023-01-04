#pragma once

#ifndef __UTILS_H__
#define __UTILS_H__
#endif

#include <stdio.h>
#include <stdint.h>

#include "./memory.h"

uint16_t sign_extend(uint16_t x, int bit_count);

// Converts big endian to little endian
uint16_t swap16(uint16_t x);

// Read the image file into memory
void read_image_file(FILE *file);
int read_image(const char *filename);

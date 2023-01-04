#pragma once

#ifndef __WIN_H__
#define __WIN_H__
#endif

#include <Windows.h>
#include <conio.h>
#include <stdint.h>

void disable_input_buffering();
void restore_input_buffering();
uint16_t check_key();

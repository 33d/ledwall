/*
 * colors.h
 *
 *  Created on: 30 Dec 2014
 *      Author: damien
 */

#ifndef COLORS_H_
#define COLORS_H_

#include <stdint.h>

uint32_t COLORS[] = {
    0xFF0000,
    0xFF0035,
    0xFF0095,
    0xFF00F4,
    0xAA00FF,
    0x4C00FF,
    0x0014FF,
    0x0073FF,
    0x00D3FF,
    0x00FFCC,
    0x00FF6D,
    0x00FF0E,
    0x51FF00,
    0xB1FF00,
    0xFFED00,
    0xFF8F00
};

#define COLORS_COUNT (sizeof(COLORS) / sizeof(uint32_t))

#endif /* COLORS_H_ */

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
    0x00FFFF51,
    0x0051FF51,
    0x0072FF51,
    0x00B3FF51,
    0x00F1CC51,
    0x00FF8A51,
    0x00FF5159,
    0x00FF519B,
    0x00FF51DC,
    0x00FF51FF,
    0x00E051FF,
    0x009F51FF,
    0x006182FF,
    0x0051C4FF,
    0x0051FFF9,
    0x0051FFB7
};

#define COLORS_COUNT (sizeof(COLORS) / sizeof(uint32_t))

#endif /* COLORS_H_ */

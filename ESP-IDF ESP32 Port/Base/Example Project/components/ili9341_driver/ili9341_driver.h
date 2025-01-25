//enable ili9341 driver
#if 1
#ifndef ILI9341_DRIVER_H
#define ILI9341_DRIVER_H

//include
#include<stdio.h>
#include<stdint.h>

//ili9341 init
void ili9341_init();
//ili9341 flash
void ili9341_flash(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint16_t*color);

#endif//#ifndef ILI9341_DRIVER_H
#endif//#if 1

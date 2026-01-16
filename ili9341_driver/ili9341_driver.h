//启用ILI9341驱动
#if 1
#ifndef ILI9341_DRIVER_H
#define ILI9341_DRIVER_H

//依赖
#include<stdint.h>

//初始化ILI9341
uint8_t ili9341_init();
//刷新ILI9341
uint8_t ili9341_flash(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint16_t*color);

#endif//#ifndef ILI9341_DRIVER_H
#endif//#if 1

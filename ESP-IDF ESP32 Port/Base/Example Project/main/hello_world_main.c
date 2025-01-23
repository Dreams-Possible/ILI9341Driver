#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"

#include"ili9341_driver.h"

void app_main(void)
{
    //spi init
    //spi_init();

    //st7735 init all
    ili9341_init();

    //simple test
    uint16_t*data=(uint16_t*)malloc(240*320*sizeof(uint16_t));
    uint16_t color=0;
    for(uint32_t i=0;i<240*320;++i)
    {
        data[i]=color;
        ++color;
    }

    //st7735 flash color
    ili9341_flash(0,0,240-1,320-1,data);
}

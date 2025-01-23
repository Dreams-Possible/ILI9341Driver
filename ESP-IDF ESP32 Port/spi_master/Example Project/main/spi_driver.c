#include"spi_driver.h"
//enable spi driver
#ifdef SPI_DRIVER_H

//config
#define SPI_COM SPI2_HOST
#define SPI_SCLK 12
#define SPI_MOSI 11
#define SPI_MISO 13

//spi init
void spi_init();

//spi init
void spi_init()
{
    spi_bus_config_t config={0};
    config.mosi_io_num=SPI_MOSI;
    config.miso_io_num=SPI_MISO;
    config.sclk_io_num=SPI_SCLK;
    config.quadwp_io_num=-1;
    config.quadhd_io_num=-1;
    spi_bus_initialize(SPI_COM,&config,SPI_DMA_CH_AUTO);
}

#endif//#ifdef SPI_DRIVER_H

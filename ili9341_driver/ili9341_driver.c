#include"ili9341_driver.h"
//启用ILI9341驱动
#ifdef ILI9341_DRIVER_H
#include<stddef.h>

//配置定义
#define DC 21
#define RST 47//设置为-1代表不使用
#define LED 14//设置为-1代表不使用
#define HOR 240//横向像素
#define HOR_OFF 0//横向像素偏移
#define VER 320//纵向像素
#define VER_OFF 0//纵向像素偏移
#define DIR 0//旋转方向
#define BRG 1//是否使用BGR格式颜色
#define INV 0//是否启用反色

//某些厂商的横向屏幕配置示例
// //配置定义
// #define DC 21
// #define RST 47//设置为-1代表不使用
// #define LED 14//设置为-1代表不使用
// #define HOR 320//横向像素
// #define HOR_OFF 0//横向像素偏移
// #define VER 240//纵向像素
// #define VER_OFF 0//纵向像素偏移
// #define DIR 0//旋转方向
// #define BRG 1//是否使用BGR格式颜色
// #define INV 0//是否启用反色

//某些厂商的纵向屏幕配置示例
// //配置定义
// #define DC 21
// #define RST 47//设置为-1代表不使用
// #define LED 14//设置为-1代表不使用
// #define HOR 240//横向像素
// #define HOR_OFF 0//横向像素偏移
// #define VER 320//纵向像素
// #define VER_OFF 0//纵向像素偏移
// #define DIR 2//旋转方向
// #define BRG 1//是否使用BGR格式颜色
// #define INV 0//是否启用反色

//寄存器地址定义
#define SWRESET 0x01
#define SLPOUT 0x11
#define INVON 0x21
#define INVOFF 0x20
#define COLMOD 0x3a
#define MADCTL 0x36
#define DISPON 0x29
#define GMCTRP1 0xe0
#define GMCTRN1 0xe1

//IO设置
static void io(uint16_t pin,uint8_t level);
//毫秒级延迟
static void delay(uint32_t ms);
//发送命令
static void send_cmd(uint8_t cmd);
//发送数据
static void send_data(uint8_t data);
//发送颜色数据
static void send_color(uint16_t*data,uint32_t length);
//用户初始化
static uint8_t init_user();
//软件初始化
static void init_soft();
//初始化ILI9341
uint8_t ili9341_init();
//刷新ILI9341
void ili9341_flash(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint16_t*color);

//IO设置
static void io(uint16_t pin,uint8_t level)
{
    //gpio_set(pin,level);
    return;
}

//毫秒级延迟
static void delay(uint32_t ms)
{
    //osdelay(ms);
    return;
}

//发送命令
static void send_cmd(uint8_t cmd)
{
    io(DC,0);
    //spi_send(cmd);
    return;
}

//发送数据
static void send_data(uint8_t data)
{
    io(DC,1);
    //spi_send(data);
    return;
}

//发送颜色数据
static void send_color(uint16_t*data,uint32_t length)
{
    io(DC,1);
    if(data==NULL||length==0)
    {
        return;
    }
    while(length)
    {
        //spi_send((uint8_t)(*data>>8));
        //spi_send((uint8_t)*data);
        ++data;
        --length;
    }
    return;
}

//用户初始化
static uint8_t init_user()
{
    //spi_init();
    //gpio_init();
    return 0;
}

//软件初始化
static void init_soft()
{
    //关闭背光
    if(LED!=-1)
    {
        io(LED,0);
    }
    //硬件复位
    if(RST!=-1)
    {
        io(RST,1);
        io(RST,0);
        io(RST,1);
        delay(200);
    }
    //发送初始化代码
    send_cmd(SWRESET);
    delay(200);
    send_cmd(SLPOUT);
    delay(200);
    if(INV)
    {
        send_cmd(INVON);
    }else
    {
        send_cmd(INVOFF);
    }
    send_cmd(COLMOD);
    send_data(0x55);
    send_cmd(MADCTL);
    uint8_t bgr=0;
    if(BRG)
    {
        bgr=0x08;
    }
    switch(DIR)
    {
        case 0:
            send_data(0x80|bgr);
        break;
        case 1:
            send_data(0x40|bgr);
        break;
        case 2:
            send_data(0xe0|bgr);
        break;
        case 3:
            send_data(0x20|bgr);
        break;
        default:
            send_data(0x80|bgr);
        break;
    }
    send_cmd(GMCTRP1);
    send_data(0x0F);
    send_data(0x31);
    send_data(0x2B);
    send_data(0x0C);
    send_data(0x0E);
    send_data(0x08);
    send_data(0x4E);
    send_data(0xF1);
    send_data(0x37);
    send_data(0x07);
    send_data(0x10);
    send_data(0x03);
    send_data(0x0E);
    send_data(0x09);
    send_data(0x00);
    send_cmd(GMCTRN1);
    send_data(0x00);
    send_data(0x0E);
    send_data(0x14);
    send_data(0x03);
    send_data(0x11);
    send_data(0x07);
    send_data(0x31);
    send_data(0xC1);
    send_data(0x48);
    send_data(0x08);
    send_data(0x0F);
    send_data(0x0C);
    send_data(0x31);
    send_data(0x36);
    send_data(0x0F);
    send_cmd(DISPON);
    delay(200);
    //启用背光
    if(LED!=-1)
    {
        io(LED,1);
    }
    return;
}

//初始化ILI9341
uint8_t ili9341_init()
{
    if(init_user())
    {
        return 1;
    }
    init_soft();
    return 0;
}

//刷新ILI9341
void ili9341_flash(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint16_t*color)
{
    //检查参数
    if(x2<x1||y2<y1||color==NULL)
    {
        return;
    }
    if(x1<0)
    {
        return;
    }
    if(y1<0)
    {
        return;
    }
    if(x2>=HOR)
    {
        return;
    }
    if(y2>=VER)
    {
        return;
    }
    //刷新
    uint8_t data=0;
    //X轴坐标
    send_cmd(0x2a);
    data=(uint8_t)(((uint16_t)x1+HOR_OFF)>>8);
    send_data(data);
    data=(uint8_t)((uint16_t)x1+HOR_OFF);
    send_data(data);
    data=(uint8_t)(((uint16_t)x2+HOR_OFF)>>8);
    send_data(data);
    data=(uint8_t)((uint16_t)x2+HOR_OFF);
    send_data(data);
    //Y轴坐标
    send_cmd(0x2b);
    data=(uint8_t)(((uint16_t)y1+VER_OFF)>>8);
    send_data(data);
    data=(uint8_t)((uint16_t)y1+VER_OFF);
    send_data(data);
    data=(uint8_t)(((uint16_t)y2+VER_OFF)>>8);
    send_data(data);
    data=(uint8_t)((uint16_t)y2+VER_OFF);
    send_data(data);
    //发送颜色
    send_cmd(0x2c);
    uint32_t length=(x2-x1+1)*(y2-y1+1);
    send_color(color,length);
    return;
}

#endif//#ifdef ILI9341_DRIVER_H

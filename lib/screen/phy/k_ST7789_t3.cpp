#include <phy/k_ST7789_t3.h>
#include "kled.h"
extern K_LED debugr_LED;
K_ST7789_t3::K_ST7789_t3(uint8_t CS = 255, uint8_t DC = 255, uint8_t MOSI = 255, uint8_t SCLK = 255, uint8_t RST = 255) : 
    screen(CS, DC, MOSI, SCLK, RST)
{
    //this->screen = screen;
}

k_err K_ST7789_t3::init()
{
    debugr_LED.on();
    screen.init(240,320);
    screen.setRotation(1);
    screen.invertDisplay(false);
    screen.fillScreen(ST77XX_BLACK);
    return K_ERR_NONE;
}

k_err K_ST7789_t3::fillScreen(uint16_t color)
{
    screen.fillScreen(color);

    return K_ERR_NONE;

}

k_err K_ST7789_t3::print(char * str)
{
    screen.print(str);

    return K_ERR_NONE;
}

k_err K_ST7789_t3::println(char * str)
{
    screen.println(str);

    return K_ERR_NONE;
}
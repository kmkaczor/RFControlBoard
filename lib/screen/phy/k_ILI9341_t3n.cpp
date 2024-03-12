#include "phy/k_ILI9341_t3n.h"

K_ILI9341_t3n::K_ILI9341_t3n(uint8_t CS, uint8_t DC, uint8_t RST, uint8_t MOSI,
    uint8_t SCLK, uint8_t MISO)  : screen(CS, DC, RST, MOSI, SCLK, MISO)
{
}

k_err K_ILI9341_t3n::init()
{
    screen.begin();

    return K_ERR_NONE;
}

#include "k_XPT2046.h"

K_XPT2046::K_XPT2046(uint8_t CS, uint8_t IRQ) : touch(CS, IRQ)
{

}

k_err K_XPT2046::init()
{
    touch.begin(SPI1);
    touch.setRotation(1);

    return K_ERR_NONE;
}

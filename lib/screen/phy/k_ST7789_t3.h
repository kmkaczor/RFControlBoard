#ifndef _K_ST7789_t3
#define _K_ST7789_t3

#include <ST7789_t3.h>

#include "phy/phyk_screen.h"

class K_ST7789_t3 : public K_SModule
{
public:
    K_ST7789_t3(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    k_err init();

    k_err fillScreen(uint16_t);
    k_err print(char *);
    k_err println(char *);

protected:
    ST7789_t3 screen;
};

#endif
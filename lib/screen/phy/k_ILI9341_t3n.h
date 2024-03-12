#ifndef _K_ILI9341_T3N
#define _K_ILI9341_T3N
#include <ILI9341_t3n.h>

#include "phy/phyk_screen.h"

class K_ILI9341_t3n : public K_SModule 
{
    public:   
    K_ILI9341_t3n(uint8_t CS = 255, uint8_t DC = 255, uint8_t RST = 255, uint8_t MOSI = 255,
        uint8_t SCLK = 255, uint8_t MISO = 255);
    k_err init();
   
    int getMWidth() { return ILI9341_TFTWIDTH; };
    int getMaxHeight() { return ILI9341_TFTHEIGHT; };
    k_err print(char *);
    protected:
    ILI9341_t3n screen;
};

#endif
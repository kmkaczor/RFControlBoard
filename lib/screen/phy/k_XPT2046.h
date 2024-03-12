#ifndef _K_XPT2046
#define _K_XPT2046

#include "phyk_screen.h"
#include <XPT2046_Touchscreen.h>

class K_XPT2046 : public K_TModule
{
    public:
    K_XPT2046(uint8_t, uint8_t);
    k_err init();


    private:
    XPT2046_Touchscreen touch;
};
#endif
#ifndef _K_SCREEN
#define _K_SCREEN

#include <array>
#include "kscreen_area.h"
//#include "screen/phy/k_ILI9341_t3n.h"
#include "phy/phyk_screen.h"

// TFT
#include "phy/k_ILI9341_t3n.h"
#include "phy/k_ST7789_t3.h"

// Touchscreens
#include "phy/k_XPT2046.h"

#ifndef K_AREAS_MAX
#define K_AREAS_MAX 16
#endif
// Includes common handling of display and touchscreen
class K_Display 
{
    private:
    unsigned int width {};
    unsigned int height {};
    

    public:
    K_AREA background;
    //phyk_Touch  *touch;

    K_Display();
    K_Display(K_SModule *);

    std::array<K_AREA, K_AREAS_MAX> areas;
    k_err init();
    k_err println(char *);
    void update();

    protected:
    K_SModule *screen;
    K_TModule *touch;
    private:
};

#endif
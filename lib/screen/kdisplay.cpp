#include "kdisplay.h"


K_Display::K_Display(K_SModule * mod = NULL) : screen(mod)
{
}

k_err K_Display::init()
{
    if (screen == NULL)
        return K_ERR_SCREEN_NO_DEVICE;

    screen->init();

    return K_ERR_NONE;
}

k_err K_Display::println(char * s)
{
    if (screen == NULL)
        return K_ERR_SCREEN_NO_DEVICE;
    
    screen->println(s);
    
    return K_ERR_NONE; 
}

void K_Display::update()
{
    for (int i = 0; i < areas.size(); i++)
    {
        K_AREA *a = &areas[i];
        if (a->update == true)
        {
            K_CANVAS *c = a->get_canvas();
            c->fillScreen(a->background_color);
            c->println();
        }
    }
}
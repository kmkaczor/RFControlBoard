#ifndef K_SCREEN_GUARD
#define K_SCREEN_GUARD
#include <iostream>
#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen.h>
#include <type_traits>
#include "kdevices.h"
#include "kscreen_area.h"
#include <vector>
#include <string>
#include <type_traits>
#include <ILI9341_t3n.h>
using namespace std;

// EXTMEM K_CANVAS canvases[255](0,0);
// EXTMEM GFXcanvas16 c;

template <class S, class T>
class Screen : public KDevice
{
private:
    int background_color_default = 0;
    int text_color_default = 1;
    int num_areas = 0;
    int _get_screen_height();
    int _get_screen_width();

protected:
    vector<K_AREA *> areas;
    unsigned int width = 0;
    unsigned int height = 0;

public:
    S *screen;
    T *touch;
    Screen(S *, T *, void (*)() = NULL, uint8_t = 255);
    kd_err_code getTouchPoint(auto, auto, auto);
    kd_err_code setScreen(S *);
    void setScreenIRQ((void *), uint8_t);
    kd_err_code setTouchIRQ(void (*)(), uint8_t);
    kd_err_code setTouch(T *);
    // Screen(unsigned int cs, unsigned int dc, unsigned int rst, unsigned int mosi, unsigned int sck, unsigned int miso);
    kd_err_code begin();

    kd_err_code redraw();
    kd_err_code clear();
    kd_err_code newArea(int, int, int, int);
    kd_err_code newTextArea(int, int, int, int, string *);
    kd_err_code addText(string *, int = -1);
    
    kd_err_code blank();
};

/**/
template <class S, class T>
Screen<S, T>::Screen(S *screen, T *touch, void (*isr_touch)(), uint8_t irq_pin_touch) 
{
    setScreen(screen);
    setTouch(touch);
    setTouchIRQ(isr_touch, irq_pin_touch);

    // attachInterrupt(digitalPinToInterrupt(device-), isr_button_reset, HIGH);
}

template <class S, class T>
kd_err_code Screen<S, T>::setScreen(S *screen)
{
    if (screen == NULL)
        return K_ERR_SCREEN_NO_DEVICE;

    this->screen = screen;
    if (std::is_same<S, ILI9341_t3n>::value)
    {
        // this->screen->begin();
        // this->newArea(0, 0, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
        this->background_color_default = ILI9341_BLACK;
        this->text_color_default = ILI9341_WHITE;
    }
    else
    {
    }

    return K_ERR_NONE;
}

template <class S, class T>


template <class S, class T>
int Screen<S, T>::_get_screen_height()
{
    if (std::is_same<S, ILI9341_t3n>::value)
    {
        return ILI9341_TFTHEIGHT;
    }
    
    return 0;
}

template <class S, class T>
int Screen<S, T>::_get_screen_width()
{
    if (std::is_same<S, ILI9341_t3n>::value)
    {
        return ILI9341_TFTWIDTH;
    }
    
    return 0;
}

template <class S, class T>
kd_err_code Screen<S, T>::setTouch(T *touch)
{
    if (touch == NULL)
        return K_ERR_TOUCH_NO_DEVICE;
    this->touch = touch;
    if (std::is_same<T, XPT2046_Touchscreen>::value)
    {
        // touch->begin(SPI1);
        //  attachInterrupt(digitalPinToInterrupt(40U), isr_xpt, RISING);
    }
    else
    {
    }

    return K_ERR_NONE;
}

template <class S, class T>
kd_err_code Screen<S, T>::setTouchIRQ(void (*isr_touch)(), uint8_t irq_pin_touch)
{
    if (isr_touch == NULL)
        return K_ERR_TOUCH_INVALID_IRQ;

    attachInterrupt(digitalPinToInterrupt(irq_pin_touch), isr_touch, HIGH);

    if (std::is_same<T, XPT2046_Touchscreen>::value)
    {
    }

    return K_ERR_NONE;
}

template <class S, class T>
kd_err_code Screen<S, T>::begin()
{
    // Start Screen
    if (std::is_same<ILI9341_t3n, S>::value)
    {
        this->screen->begin();
    }

    // Start Touch
    if (std::is_same<T, XPT2046_Touchscreen>::value)
    {
        touch->begin(SPI1);
    }

    return K_ERR_NONE;
}
template <class S, class T>
kd_err_code Screen<S, T>::newArea(int x, int y, int width, int height)
{
    K_AREA *area = new K_AREA(x, y, width, height);
    area->set_bgcolor(this->background_color_default);
    // area->set_textcolor(this->text_color_default);

    areas.push_back(area);

    return K_ERR_NONE;
}

template <class S, class T>
kd_err_code Screen<S, T>::newTextArea(int x, int y, int width, int height, std::string *text_line)
{
    K_TEXT *area = new K_TEXT(x, y, width, height, text_line);

    area->set_bgcolor(this->background_color_default);
    area->set_textcolor(this->text_color_default);
    areas.push_back(area);

    // K_CANVAS *c = (K_CANVAS *)extmem_malloc(sizeof(K_CANVAS));
    // new (c) K_CANVAS(width, height);

    return K_ERR_NONE;
}

template <class S, class T>
// kd_err_code Screen<S, T>::addText(string *text_line, K_AREA *a)
kd_err_code Screen<S, T>::addText(string *text_line, int i)
{
    kd_err_code err = K_ERR_NONE;
    int16_t x = 0;
    int16_t y = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    if ((int)areas.size() < i)
        return K_ERR_SCREEN_INVALID_AREA;
    else if (i < 0)
        i = 0;

    K_TEXT *area = areas[i];

    if (area == NULL)
        screen->println("fuck this, area was null");

    screen->println("test");
    // Obtain data here
    if (std::is_same<ILI9341_t3n, S>::value)
    {
        this->screen->getTextBounds(
            text_line->c_str(),
            // 1, 2, 3, 4, 5, 6,
            area->x + area->width,
            area->y + area->height,
            (&x),
            (&y),
            (&width),
            (&height));
        this->screen->printf("x:%d,y:%d,x1:%d,y1:%d,width:%d,height:%d\n",
                             area - x, height, y);
    }
    else
        return K_ERR_SCREEN_NO_DEVICE;

    err = newTextArea(area->x,
                      area->y,
                      area->width,
                      area->height,
                      text_line);
    return err;
}

template <class S, class T>
kd_err_code Screen<S, T>::redraw()
{
    for (unsigned int i = 0; i < areas.size(); i++)
    //for (vector<K_AREA *> it = &areas.begin(); it != areas.end(); ++it)
    {
        K_AREA *area = areas[i];

        if (std::is_same<ILI9341_t3n, S>::value)
        {
            if (areas[i]->get_type() == 0x1)
            {
                K_TEXT *text_area = static_cast<K_TEXT *>(area);
                // this->screen->printf("X: %d,Y: %d,w: %d,h: %d\n", text_area->x, text_area->y, text_area->width, text_area->height);
                // this->screen->printf("X: %d,Y: %d,w: %d,h: %d\n%p\n", text_area->x, text_area->y, text_area->width, text_area->height, text_area);

                this->screen->drawBitmap(
                    (int16_t)text_area->x,
                    (int16_t)text_area->y,
                    (const uint8_t *)text_area->get_canvas()->getBuffer(),
                    (int16_t)text_area->width,
                    (int16_t)text_area->height,
                    (uint16_t)text_area->text_color
                    //(uint16_t) text_area->background_color
                );
            }
        }
    }

    return K_ERR_NONE;
}

template <class S, class T>
kd_err_code Screen<S, T>::blank()
{
    if (std::is_same<ILI9341_t3n, S>::value)
    {
        this->screen->fillScreen(this->background_color_default);
        this->screen->setCursor(0, 0); } else return K_ERR_SCREEN_NO_DEVICE;
    return K_ERR_NONE;
}

template <class S, class T>
kd_err_code Screen<S, T>::clear()
{
    this->blank();
    areas.clear();

    return K_ERR_NONE;
}

/*
template <class S, class T>
void Screen<S, T>::_renderAreas(list<K_AREA> area)
{
    if (std::is_same<ILI9341_t3n, T>::value)
    {
        this - device->areas;
    }
}
*/
#endif

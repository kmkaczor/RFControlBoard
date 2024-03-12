#include "kscreen.h"
//#include "config.h"
#include <ILI9341_t3n.h>
/*
template <class S, class T>
Screen<S, T>::Screen(S *screen, T *touch , void (*isr_touch)(), uint8_t irq_pin_touch)
{
    setScreen(screen);
    setTouch(touch);
    setTouchIRQ(isr_touch, irq_pin_touch);

    // attachInterrupt(digitalPinToInterrupt(device-), isr_button_reset, HIGH);
    // device->begin();
}


template <class S, class T>
kd_err_code Screen<S, T>::setScreen(S *screen)
{
    if (screen == NULL)
        return K_ERR_SCREEN_NO_DEVICE;

    this->screen = screen;
    if (std::is_same<S, ILI9341_t3n>::value)
    {
        screen->begin();
    }
    else
    {
    }
    
dfasdfsdfdsfaisdf   return K_ERR_NONE;
}

template <class S, class T>
kd_err_code Screen<S, T>::setTouch(T *touch)

    if (touch == NULL)
        return K_ERR_TOUCH_NO_DEVICE;
    this->touch = touch;
    if (std::is_same<T, XPT2046_Touchscreen>::value)
    {
        touch->begin(SPI1);
        // attachInterrupt(digitalPinToInterrupt(40U), isr_xpt, RISING);
    }
    else
    {
    }
    
    return K_ERR_NONE;
}

template <class S, class T>
kd_err_code Screen<S, T>::setTouchIRQ(void ( * isr_touch)(), uint8_t irq_pin_touch)
{
    if (isr_touch == NULL)
        return K_ERR_TOUCH_INVALID_IRQ;

    if (std::is_same<T, XPT2046_Touchscreen>::value)
    {
        attachInterrupt(digitalPinToInterrupt(irq_pin_touch), isr_touch, HIGH);
    }
    
    return K_ERR_NONE;
}


ks_err_code Screen<ILI9341_t3n>::init(unsigned int cs, unsigned int dc, unsigned int rst, unsigned int mosi, unsigned int sck, unsigned int miso)//, SPIClass &spi_ts)
{
    this->device = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, K_SPI1_MOSI, K_SPI1_SCK, K_SPI1_MISO);
    //ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, K_SPI1_MOSI, K_SPI1_SCK, K_SPI1_MISO);
    
    //if (this->device == NULL)
        //return ERR_KSCREEN_NO_DEVICE;

    // Initialize Touch Screen
    
    //attachInterrupt(digitalPinToInterrupt(TS_IRQ), isr_xpt, FALLING);
    //NVIC_SET_PRIORITY(digitalPinToInterrupt(TS_IRQ), 1);
    //
    this->device.begin();
    this->init_state = true;
}

*/
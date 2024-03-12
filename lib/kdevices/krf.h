#ifndef K_RF_GUARD
#define K_RF_GUARD
#include "Arduino.h"
#include "kdevices.h"
#include "RadioLib.h"

struct device_err
{
    int error_num = 0;
    char *error_str;
};

template <class R>
class RF : public KDevice
{
protected:
    device_err error{0};
    unsigned long long count_received{0};
    unsigned long long count_sent{0};
    k_err recieveHandler();

public:
    RF();
    RF(R *);
    R *device;
    k_err begin();
    k_err send();
    k_err setRecieveIRQ(void (*)(), uint8_t);
    void _increment() { this->count_received++; };
};

template <class R>
RF<R>::RF(R *device)
{
    if (device == NULL)
        return;

    this->device = device;
}

template <class R>
k_err RF<R>::begin()
{
    if (std::is_same<R, RFM95>::value)
    {
        int stat = this->device->begin(915);
        if (stat != RADIOLIB_ERR_NONE)
            return K_ERR_INVALID_DEVICE;
            // logger("RF95 Fail");
            //this->device->setDio0Action(isr_rf95, RISING);
        this->device->setDio0Action(isr_rf95, RISING);
        this->device->startReceive();
    }

    return K_ERR_NONE;
}

template <class R>
k_err RF<R>::setRecieveIRQ(void (*isr_rf)(), uint8_t isr_pin_rf)
{

#if defined(ARDUINO_TEENSY41) || defined(ARDUINO_TEENSY40)
#else
    #warning("No valid driver found!");
//  attachInterrupt(digitalPinToInterrupt(isr_pin_rf), isr_rf, HIGH);
#endif

    if (this->device == NULL)
        return K_ERR_RF_NO_DEVICE;

    if (std::is_same<R, Module>::value)
    {
        this->device->setDio0Action(isr_rf95, RISING);
        this->device->startReceive();
    }
    else
        return K_ERR_INVALID_DEVICE;
    return K_ERR_NONE;
}


#endif
#include <math.h>
#include <stdint.h>

#include <Arduino.h>

#include "kled.h"

#define OFF 0
#define ON 1

K_LED::K_LED(uint8_t pin = 255, bool anode = true, bool state = false) : pin(pin), anode(anode), state(state)
{
    pinMode(pin, (anode) ? OUTPUT : OUTPUT_OPENDRAIN );
    state ? on() : off();
}

void K_LED::on()
{
    if (pin == 255)
        return;
    state = ON;
    digitalWriteFast(pin, state);
}

void K_LED::off()
{
    if (pin == 255)
        return;
    state = OFF;
    digitalWriteFast(pin, state);
}

void K_LED::blink()
{
    if (pin == 255)
        return;
    state = !state;
    digitalWriteFast(pin, state);
}

K_RGB::K_RGB(uint8_t r_pin, uint8_t g_pin, uint8_t b_pin, bool anode = 1, bool state = 0) : red_pin(r_pin), green_pin(g_pin), blue_pin(b_pin)
{
    K_LED(255, anode, state);
    pinMode(red_pin, (anode) ? OUTPUT_OPENDRAIN : OUTPUT);
    pinMode(green_pin, (anode) ? OUTPUT_OPENDRAIN : OUTPUT);
    pinMode(blue_pin, (anode) ? OUTPUT_OPENDRAIN : OUTPUT);
    pinMode(pin, (anode) ? OUTPUT_OPENDRAIN : OUTPUT); // TODO

    setRGB(0, 0, 0);
}

void K_RGB::setRGB(led_val_t r_val, led_val_t b_val, led_val_t g_val)
{
    red_value = r_val;
    green_value = g_val;
    blue_value = b_val;

    this->update();
}

void K_RGB::update()
{
    switch (this->ALGO)
    {
    default:
    case (SINE):
        _sin2();
        break;
    }
    /*
    analogWriteFrequency(red_pin, 100);
    analogWriteFrequency(green_pin, 100);
    analogWriteFrequency(blue_pin, 100);
    analogWrite(red_pin, red_value);
    analogWrite(green_pin, g_Val);
    analogWrite(blue_pin, b_Val);
    */
}
void K_RGB::_sin()
{
#define K_SIN_INCREMENT 1
    
    red_value = (red_value + K_SIN_INCREMENT) % 360;
    green_value = (green_value + K_SIN_INCREMENT) % 360;
    blue_value = (blue_value + K_SIN_INCREMENT) % 360;
    
    double rad_r = ((red_value > 180) ? 0 : red_value) * PI/180;
    double rad_g = ((green_value > 180) ? 0 : green_value) * PI/180;
    double rad_b = ((blue_value > 180) ? 0 : blue_value) *  PI/180;
    
    
    analogWrite(red_pin, sin(rad_r) * 128 + 127);
    analogWrite(green_pin, 2 * sin(rad_g) * 128 + 127);
    analogWrite(blue_pin, 2 * sin(rad_b) * 128 + 127);
}
void K_RGB::_sin2()
{
#define K_INCREMENT 1

    if (red_value > 0 && blue_value == 0)
    {
        red_value -= 1;
        green_value += 1;
    }
    if (green_value > 0 && red_value == 0)
    {

        blue_value += 1;
        green_value -= 1;
    }
    if (blue_value > 0 && green_value == 0)
    {
        red_value += 1;
        blue_value -= 1;
    }
    
    //analogWrite(red_pin, sin(rad_r) * 128 + 127);
    //analogWrite(green_pin, 2 * sin(rad_g) * 128 + 127);
    //analogWrite(blue_pin, 2 * sin(rad_b) * 128 + 127);
    analogWrite(red_pin, red_value);
    analogWrite(blue_pin, blue_value);
    analogWrite(green_pin, green_value);
}
/*
void K_RGB::_sin()
{
#define K_SIN_INCREMENT 1
    double rad_r = (red_value = ((red_value + K_SIN_INCREMENT) % 360) + PI / 2) + (PI / 180);
    double rad_g = (g_Val = ((g_Val + K_SIN_INCREMENT) % 360) + PI) + (PI / 180);
    double rad_b = (b_Val = (b_Val + K_SIN_INCREMENT) % 360) + (PI / 180);
    
    red_value = (red_value + 1) % 360;
    red_value = (b_Val + 1) % 360;
    red_value = (g_Val + 1) % 360;
    
    rad_r = (red_value * PI/180);
    rad_g = (g_Val * PI/180) + PI;
    rad_b = (b_Val * PI/180) + PI/2;


    if (rad_r < 0)
        rad_r = 0;
    if (rad_g < 0)
        rad_g = 0;
    if (rad_b < 0)
        rad_b = 0;
    rad_r = sin(rad_r);
    rad_g = sin(rad_g);
    rad_b = sin(rad_b);
    // analogWriteFrequency(red_pin, rad_r * 100);
    // analogWriteFrequency(green_pin, rad_b * 100);
    // analogWriteFrequency(blue_pin, rad_g * 100);
    // analogWriteFrequency(red_pin,10);
    // analogWriteFrequency(green_pin, 10);
    // analogWriteFrequency(blue_pin,10);
    analogWrite(red_pin, rad_r * MAX_LED_VALUE);
    analogWrite(green_pin, rad_g * MAX_LED_VALUE);
    analogWrite(blue_pin, rad_b * MAX_LED_VALUE);
}

*/

char * K_RGB::to_string()
{
    char buf[222] {NULL};
    snprintf(buf, sizeof(buf), "Red: %-u\nBlue: %-u\nGreen: %-u\n", this->red_value, this->green_value, this->blue_value);
    Serial.println(buf);
    return buf;
}

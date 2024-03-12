#ifndef K_LED_GUARD
#define K_LED_GUARD

//#include <stdlib.h>
#include <stdint.h>
#include <limits.h> // For INT_MAX

typedef uint8_t led_val_t;

#define MAX_LED_VALUE 255
//(INT_MAX / 2 - 1)
    
class K_LED
{
    
protected:
    uint8_t pin;
    bool anode;
    bool state;
public:
    //K_LED(uint8_t r_pin, uint8_t g_pin, uint8_t b_pin, uint8_t is_anode = 1) : r_Pin(r_pin), g_Pin(g_pin), b_Pin(b_pin), anode(is_anode){};
    K_LED(uint8_t, bool, bool);
    void blink();
    void on();
    void off();
   
};

class K_RGB: public K_LED
{
    private:
        // Pin numbers
        uint8_t red_pin;
        uint8_t green_pin;
        uint8_t blue_pin;
        // Values stored in degrees
        led_val_t red_value;
        led_val_t green_value;
        led_val_t blue_value;
    protected:
        enum ALGO {
            HSV,
            SINE,
            PHSV
        } ALGO;
        
        void _sin();
        void _sin2();

    public:
        K_RGB(uint8_t, uint8_t , uint8_t , bool, bool);
        void setRGB(led_val_t, led_val_t, led_val_t);
        void update();
        char * to_string();
};
//#ifdef __cplusplus
//}
//#endif

#endif
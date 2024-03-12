#ifndef K_DEVICES_GUARD
#define K_DEVICES_GUARD

#include <inttypes.h>

typedef int_least8_t k_err;

#define K_ERR_NONE 1
#define K_ERR_INVALID_DEVICE 2
#define K_ERR_SCREEN_NO_DEVICE 100
#define K_ERR_SCREEN_INVALID_AREA 101
#define K_ERR_TOUCH_NO_DEVICE 200
#define K_ERR_TOUCH_INVALID_IRQ 201
#define K_ERR_RF_NO_DEVICE 241



class K_Device {
    
    private:
        bool init_state;
    public:
        k_err init();
};


#endif

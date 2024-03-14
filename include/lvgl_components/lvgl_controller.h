#ifndef _LVGL_MASTER_CONTROLLER
#define _LVGL_MASTER_CONTROLLER

// #include "lvgl_ts.h"
#include <lvgl.h>
#include <array>
#include "lvgl_display.h"
#include "theme/theme_based.h"
// #include "config.h"

extern K_LED debugp_LED;

class LVGL_Controller {
public:
    // constexpr static DisplayTouchController dtc[];
    //_LVGL_Controller(DisplayTouchController* dsc[]) {};
    // template <std::size_t N>
    // LVGL_Controller(std::initializer_list<DisplayTouchController> arr) : dsc(arr){};
    LVGL_Controller(DisplayTouchController* arr);

    //    template <size_t N> LVGL_Controller(std::array<DisplayTouchController *, N> arr);
    template<size_t Numeric>
    LVGL_Controller(std::array<DisplayTouchController*, Numeric> arr) : dtc(arr)
    {
        lv_init();
        for ( auto dt: this->dtc )
        {
            _init_dtc(dt);
        }
    };

    // LVGL_Controller(){};
    std::array<DisplayTouchController*, 1> dtc;
    lv_obj_t* msg_logbox;

    void log_println(const char*);

    void log_printf(const char*, ...);

    // DisplayTouchController get_display(size_t n) {return dsc[n];};
    void init_logger_list(lv_display_t* display);

    void link_display();

    void link_ts();

    void link_();

private:
    void _init_dtc(DisplayTouchController*);
    // lv_style_t msg_logbox_style;
    // lv_obj_t* msg_logbox = lv_list_create();
};

extern LVGL_Controller UI_Controller;
#endif
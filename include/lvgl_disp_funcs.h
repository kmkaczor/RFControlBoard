#ifndef _K_DISP_FUNCS
#define _K_DISP_FUNCS

#include <lvgl.h>
#include <type_traits>

//void my_disp_flush(lv_display_t *disp, const lv_area_t * area, lv_color_t * color_p);
void read_touch(lv_indev_t *touchdev, lv_indev_data_t *data);
lv_span_t * init_lv_log_box();
void lv_add_log_entry(char *);
void _init_lvgl();
void lvgl_screen_calibrate_ts();

#endif
#ifndef K_MISC_GUARD
#define K_MISC_GUARD

#include <string.h>
//#include <QNEthernet.h>

#define init_lvgl _init_lvgl

void init_spi();
void init_pins();
void init_interrupts();
void init_peripherals();
void init_lvgl();



void tprint(String);
void tprintln(String);
void logger(String);
// static void init_lvgl();

#include "lvgl.h"
//void my_disp_flush(lv_display_t *disp, const lv_area_t * area, lv_color_t * color_p);
//void read_ts_cb(lv_indev_t *touchdev, lv_indev_data_t *data);
char * get_log_debug();
//String IPv4ToString(const IPAddress &);
//struct ts_cal_values calibrate_ts(int x[3], int y[3], const int (&m)[3][3]);

#endif
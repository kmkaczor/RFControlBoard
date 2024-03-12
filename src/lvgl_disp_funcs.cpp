#include <lvgl.h>
#include "lvgl_disp_funcs.h"
#include <Arduino.h>
#include <usb_serial.h>
#include <TimeLib.h>
#include <ST7789_t3.h>
#include <XPT2046_Touchscreen.h>
#include "config.h"
#include "kled.h"

extern ST7789_t3 tft;
extern XPT2046_Touchscreen xpt;
extern K_LED debugp_LED;

//lv_display_t * lvgl_display0;
//lv_indev_t *lvgl_ts0;
//lv_obj_t * lvgl_logbox;





/*
void event_draw_point(lv_event_t * event)
{
    static lv_obj_t * p = lv_obj_create(lv_screen_active());
    lv_obj_set_size(p, 5, 5);
    
    lv_point_t pxy;
    lv_indev_get_point(lvgl_ts0, &pxy);
    lv_obj_set_pos(p, pxy.x, pxy.y);
    
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_make(255, 255, 0));
    lv_style_set_line_width(&style, LV_STATE_DEFAULT);
    lv_style_set_radius(&style, LV_RADIUS_CIRCLE);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_obj_add_style(p, &style, 0);

}

void lvgl_screen_calibrate_ts()
{
    lv_obj_t * scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    //lv_obj_set_style_bg_color(scr, lv_color_white, 0);

    lv_obj_t * p1 = lv_obj_create(scr);
    lv_obj_t * p2 = lv_obj_create(scr);
    lv_obj_t * p3 = lv_obj_create(scr);
    lv_obj_set_size(p1, 5, 5);
    lv_obj_set_pos(p1, 25, 125);
    lv_obj_set_size(p2, 5, 5);
    lv_obj_set_pos(p2, 300, 15);
    lv_obj_set_size(p3, 5, 5);
    lv_obj_set_pos(p3, 110, 180);


    //lv_obj_set_style_circle_width(p1, LV_STATE_DEFAULT, 5);  // Set circle width
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_line_width(&style, LV_STATE_DEFAULT);
    lv_style_set_radius(&style, LV_RADIUS_CIRCLE);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_obj_add_style(p1, &style, 0);
    lv_obj_add_style(p2, &style, 0);
    lv_obj_add_style(p3, &style, 0);

    lv_obj_add_event_cb(scr, event_draw_point, LV_EVENT_PRESSING, NULL);    
    lv_screen_load(scr);
}
*/



void lvgl_update_time()
{
    //static lv_obj_t * time = lv_textarea_create(lv_screen_active());
    //static lv_obj_t * time = lv_label_create(lv_screen_active());
    //lv_label_set_text_fmt
    //char timestr[35] {0};
    /*
    static char timestr[35] {"Cuck"};
    snprintf(timestr, 34, "%d %d, %d:%d", month(), day(), hour(), minute());
    //lv_label_set_text(time, timestr);
    lv_textarea_set_text(time, timestr);
    lv_obj_set_pos(time, lv_disp_get_hor_res(lvgl_display0) - 80, lv_disp_get_ver_res(lvgl_display0) * 4 / 5);
    lv_obj_set_width(time, 80);
    lv_obj_set_height(time, 40);
    lv_obj_set_style_text_color(time, lv_color_white(), 0);
    lv_obj_set_style_bg_color(time, lv_color_black(), 0);
    */
}
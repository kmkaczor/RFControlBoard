#include "config.h"
// LVGL_Controller(std::array<)
#include "ST7789_t3.h"
#include <stdio.h>
extern ST7789_t3 tft0;
// DisplayTouchController** LVGL_Controller::dsc = nullptr;
/*
 *
 *
 *
 *
 *
 */
static lv_style_t msg_logbox_style;
static lv_style_t msg_logbox_text;
void LVGL_Controller::init_logger_list(lv_display_t* display)
{
    static lv_obj_t* cont_main = lv_obj_create(lv_screen_active());
    static lv_obj_t* cont_win = lv_obj_create(cont_main);
    static lv_obj_t* cont_bnmx = lv_obj_create(cont_main);

    lv_obj_set_size(cont_main, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_layout(cont_main, LV_LAYOUT_FLEX);
    //lv_obj_set_style_pad_all(cont_main, 0, 0);


    lv_obj_set_flex_flow(cont_main, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_grow(cont_win, 4); // 4/5 = 80%
    lv_obj_set_flex_grow(cont_bnmx, 1); // 1/5 = 20%

    lv_obj_set_size(cont_bnmx,LV_PCT(100), LV_PCT(100));
    lv_obj_set_size(cont_win, LV_PCT(100), LV_PCT(100));
    //lv_obj_set_flex_flow(cont_window, LV_FLEX_FLOW_COLUMN);

    //lv_obj_set_align(cont_bnmx, LV_ALIGN_CENTER);
    static const char * btnm_map[] = {LV_SYMBOL_EYE_OPEN, LV_SYMBOL_SD_CARD, LV_SYMBOL_WIFI, LV_SYMBOL_ENVELOPE, LV_SYMBOL_DIRECTORY,
        LV_SYMBOL_AUDIO, LV_SYMBOL_FILE};
    static lv_obj_t* btnmx = lv_buttonmatrix_create(cont_bnmx);
    lv_buttonmatrix_set_map(btnmx, btnm_map);
    //lv_obj_set_size(btnmx, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_align(btnmx, LV_ALIGN_TOP_LEFT);

    //msg_logbox = lv_list_create(lv_scr_act());
    msg_logbox = lv_list_create(cont_win);

    lv_style_init(&msg_logbox_style);
    //lv_obj_set_size(msg_logbox, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    //lv_style_set_border_width(&msg_logbox_style, 3);
    //lv_style_set_pad_all(&msg_logbox_style, 3);
    lv_style_set_text_font(&msg_logbox_style, &lv_font_unscii_8);
    lv_style_set_bg_color(&msg_logbox_style, lv_color_black());
    lv_style_set_text_color(&msg_logbox_style, lv_color_white());

    //lv_obj_set_width(msg_logbox, lv_disp_get_hor_res(disp) - 1);
    //lv_obj_set_height(msg_logbox, lv_disp_get_ver_res(disp) * 4 / 5 - 1);
    //lv_obj_set_size(msg_logbox, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    //lv_obj_set_align(msg_logbox, LV_ALIGN_TOP_LEFT);
    //lv_obj_set_pos(msg_logbox, 0, 0);
    lv_obj_add_style(msg_logbox, &msg_logbox_style, 0);
    lv_style_set_width(&msg_logbox_style, LV_PCT(100));
    lv_style_set_height(&msg_logbox_style, LV_SIZE_CONTENT);

    // static lv_obj_t * button1 = lv_button_create(lv_screen_active());
    // static lv_obj_t *button1_label = lv_label_create(button1);
    // lv_label_set_text(button1_label, LV_SYMBOL_BELL);
}
void add_log_entry(char *entry)
{
    // lv_obj_t *text = lv_list_add_text(msg_logbox, entry);
    // lv_obj_set_style_text_color(text, lv_color_white(), 0);
    // lv_obj_set_style_bg_color(text, lv_color_black(), 0);
}

LVGL_Controller::LVGL_Controller(DisplayTouchController *dtc) : dtc({dtc})
{
    lv_init();
    _init_dtc(dtc);
}

void LVGL_Controller::_init_dtc(DisplayTouchController* dtc)
{
    dtc->display = lv_display_create(320, 240);
    lv_display_set_buffers(dtc->display, dtc->disp_buf1, dtc->disp_buf2, dtc->disp_buf_size,
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(dtc->display, dtc->disp_cb);
    dtc->ts = lv_indev_create();
    lv_indev_set_type(dtc->ts, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(dtc->ts, dtc->ts_cb);
}

void LVGL_Controller::log_println(const char *entry)
{
    lv_obj_t* text = lv_list_add_text(msg_logbox, entry);
    lv_obj_add_style(text, &msg_logbox_style, 0);
}

void LVGL_Controller::log_printf(const char *fmt...)
{
    va_list args;
    va_start(args, fmt);
    char buf[64]{0};

    vsnprintf(buf, 64, fmt, args);
    log_println(buf);
    va_end(args);
}
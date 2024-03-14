#include <config.h>
#include <lvgl.h>
#include <ST7789_t3.h>
//#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen.h>
#include <kled.h>
#include "theme/theme_based.h"
// Include devices here.
ST7789_t3 tft0 = ST7789_t3(TFT_CS, TFT_DC, K_SPI1_MOSI, K_SPI1_SCK, TFT_RST);
XPT2046_Touchscreen xpt = XPT2046_Touchscreen(TS0_CS);

static uint8_t display_buffer1[TFT0_WIDTH * TFT0_HEIGHT / 10];
/* Calibration points for touch screens*/
static DisplayTouchController::ts_precalibration_data_t<int> ts0_coord = {
    {
        {{25, 125}, {110, 180}, {300, 15}} // lcd_coords
    },
    {
        {{667, 2165}, {1621, 3008}, {3756, 536}} // ts_coords
    }};
/* Initialize our default theme, theme Based" */

/* Display and touch screen mapping */

static DisplayTouchController dtc =
    DisplayTouchController(
        TFT0_HEIGHT, TFT0_WIDTH, //
        lv_theme_based_init,
        [](lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
        {
            tft0.writeRect(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1), (uint16_t *)px_map);
            // tft.updateScreenAsync();
            lv_display_flush_ready(disp); // Indicate you are ready with the flushing
        },
        [](lv_indev_t *touchdev, lv_indev_data_t *data)
        {
            if (xpt.touched())
            {
                DisplayTouchController::ts_cal_t *cal = &dtc.ts_cal;

                TS_Point p = xpt.getPoint();
                int16_t x, y;

                data->point.x = p.x;
                data->point.y = p.y;

                x = cal->x_alpha * p.x + cal->x_beta * p.y + cal->x_delta;
                (x < 0) ? data->point.x = 0 : data->point.x = x;

                data->point.x = cal->x_alpha * p.x + cal->x_beta * p.y + cal->x_delta;

                y = cal->y_alpha * p.x + cal->y_beta * p.y + cal->y_delta;
                (y < 0) ? data->point.y = 0 : data->point.y = y;

                data->point.y = cal->y_alpha * p.x + cal->y_beta * p.y + cal->y_delta;

                data->state = LV_INDEV_STATE_PRESSED;
            }
            else
            {
                data->state = LV_INDEV_STATE_RELEASED;
            }
        },

        &ts0_coord, display_buffer1, 0, sizeof(display_buffer1) / sizeof(display_buffer1[0]));

LVGL_Controller UI_Controller = LVGL_Controller({&dtc});
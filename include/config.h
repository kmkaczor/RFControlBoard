#ifndef K_CONFIG_GUARD
#define K_CONFIG_GUARD

#define LV_USE_THEME_BASED 1
#define LED_G 3U
#define LED_R 2U
#define LED_B 4U

#define BUTTON_RESET 1U

// SPI0

#define K_SPI0_SCK 13U
#define K_SPI0_MISO 12U
#define K_SPI0_MOSI 11U

// SPI1

#define K_SPI1_SCK 27U
#define K_SPI1_MISO 39U
#define K_SPI1_MOSI 26U

// TFT Pins, uses SPI1
#define TFT_DC 41U
#define TFT_CS 38U
#define TFT_RST 255U
#define TFT0_WIDTH 240
#define TFT0_HEIGHT 320
// Touchpad pins, uses SPI1
// #define T_CS 37 // Might need to be a CS1 pin 0
#define TS0_CS 0U // Might need to be a CS1 pin 0
#define TS0_IRQ 40U
#define TS0_X0 315U // Min and max X and Y values for TS calibration
#define TS0_Y0 225U
#define TS0_X1 3885U
#define TS0_Y1 3810U

// These need to be inserted post-calibration, as the calibration does not account
//      for displays with poorly misaligned touchscreens that might hit way off
//      of the displays.
//#define TS0_X_LOW_DEADZONE
//#define TS0_X_HIGH_DEADZONE
//#define TS0_Y_LOW_DEADZONE
//#define TS0_Y_HIGH_DEADZONE

// A (13,11) = (0,20)
// B (312,113) = (294,117)
// C (167,214) = (149,215)

// RFM69 Pins, SPI0
//
#define RFM69_CS 36U
#define RFM69_D0 30U
#define RFM69_RESET 29U

// RF95W Pins, SPI0
#define RFM95_NSS 37U
#define RFM95_D0 32U
#define RFM95_RESET 31U

// RF24 Pins SPI0

#define NRF24_CE 9U
#define NRF24_CSN 10U 
#define NRF24_INTERRUPT 24U

// RFC522 Pins SPI0 
#define RFC522_SCK K_SPI0_SCK
#define RFC522_MISO K_SPI0_MISO
#define RFC522_MOSI K_SPI0_MOSI
#define RFC522_NSS 37U
#define RFC522_INT 31U
#define RFC522_RST 30U
#define LV_USE_THEME_BASED 1

#include "kled.h"
#include "lvgl_controller.h"
void my_disp_flush(lv_display_t *disp, const lv_area_t * area, lv_color_t * color_p);
//void read_ts_cb(lv_indev_t *touchdev, lv_indev_data_t *data);
//extern DisplayTouchController::ts_precalibration_data_t<int> ts0_coord;//void logger(String message);
extern K_RGB status_LED;
extern K_LED debugr_LED;
extern K_LED debugp_LED;
extern LVGL_Controller UI_Controller;
#endif
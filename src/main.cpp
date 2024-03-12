//#pragma GCC optimize ("O0")
#include "SPI.h"

#include "config.h"
// #include "examples/lv_examples.h"
#include <usb_serial.h>
// Project libraries
#include "kled.h"
#include "interrupt.h"
#include "init.h"

//#include <Adafruit_ST7789.h>
//#include <ST7735_t3.h>
#include <ST7789_t3.h>
#include <XPT2046_Touchscreen.h>
#include <ILI9341_t3n.h>

K_RGB status_LED = K_RGB(LED_R, LED_G, LED_B, true, true);
K_LED debugr_LED = K_LED(7U, 1, 0);
K_LED debugp_LED = K_LED(33U, 1, 0);
extern lv_disp_t *display;// = lv_display_create(320, 240);
extern lv_indev_t *indev;
//extern ST7789_t3 tft;
extern XPT2046_Touchscreen xpt;

void setup()
{
  init_spi();
  init_pins();
  init_peripherals();
  init_interrupts();
  init_lvgl();
  //tft.println("test");
  Serial.printf("Random number: %d\n", rand() % 1000 + 1);
  UI_Controller.log_printf("Random number: %d\n", rand() % 1000 + 1);
  UI_Controller.log_println("Gaynigger");
  //lvgl_screen_calibrate_ts();

}

void loop(void)
{
  //static int status = 0;
  debugr_LED.blink();
  lv_task_handler();
  delay(50);
}

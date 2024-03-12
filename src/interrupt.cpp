#include <Arduino.h>
#include <stdio.h>

#include "config.h"
//#include <lvgl.h>
#include "interrupt.h"
//#include "klog.h"
#include "kled.h"
#include <XPT2046_Touchscreen.h>
#include <string>
#include <lvgl.h>
extern K_RGB status_LED;
//extern K_LED status_LED;
// ISR Functions

void isr_lvgl_tick()
{
   lv_tick_inc(1);
}
void isr_button_reset()
{
  SCB_AIRCR = 0x05FA0004;
  //Serial.println("button");
  delay(250);
}

void isr_timer_led()
{
  status_LED.update();
}

//ISR_PREFIX
/*
void isr_xpt()
{
  TS_Point p = xpt.getPoint();
  detachInterrupt(digitalPinToInterrupt(TS0_IRQ));
  int16_t cursor_x = ILI9341_TFTWIDTH * 3 / 4 + 1, cursor_y = ILI9341_TFTHEIGHT / 2;
  int16_t old_x, old_y;
  xpt.getCursor(&old_x, &old_y);

  if (xpt.touched())
  {
   
    logger("X= " + String(p.x) + ", Y=" +  p.y);
  }
  tft.setCursor(old_x, old_y);
  attachInterrupt(digitalPinToInterrupt(TS0_IRQ), isr_xpt, FALLING);
}
*/
/*
void isr_timer_log()
{
  static volatile position_t last_pos{0}; //{get_last_index()};
  position_t curr_index = get_last_index();

  for (position_t i = last_pos; i != curr_index; i = klog_add(i, 1))
  {
    struct log_entry *e = klog_entry(i);
    //tprintln(e->message);
    //tftdisplay.addText(new string(e->message), -1);
  }
  last_pos = curr_index;
  //tftdisplay.redraw();
}*/

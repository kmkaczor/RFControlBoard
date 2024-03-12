
#ifndef K_INTERRUPT_GUARD
#define K_INTERRUPT_GUARD

void isr_button_reset();
void isr_xpt();
void isr_timer_led();
void isr_timer_log();
void isr_rf69();
void isr_rf95();
void isr_nrf24();
void isr_lvgl_tick();

#endif
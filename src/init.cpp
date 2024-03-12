#include <SPI.h>

#include <lvgl.h>

#include "config.h"
#include "interrupt.h"
#include "kled.h"
#include "init.h"
#include <Adafruit_GFX.h>
//#include <ILI9341_t3n.h>
#include <XPT2046_Touchscreen.h>
#include <ST7789_t3.h>
// #include "klog.h"
// #include "Adafruit_MP3.h"
#include <string>
// #include "lvgl_disp_funcs.h"
//#include "lvgl_controller.h"
//#include "lvgl_display.h"

// extern DisplayTouchController::ts_precalibration_data_t<int> ts0_coord;

extern XPT2046_Touchscreen xpt;
extern ST7789_t3 tft0;//= ST7789_t3(TFT_CS, TFT_DC, K_SPI1_MOSI, K_SPI1_SCK, TFT_RST);
// ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, K_SPI1_MOSI, K_SPI1_SCK, K_SPI1_MISO);
// ST7789_t3 tft = ST7789_t3(TFT_CS, TFT_DC, TFT_RST);
// LVGL_Display_ST7789_t3 tft0 = LVGL_Display_ST7789_t3(TFT_CS, TFT_DC, K_SPI1_MOSI, K_SPI1_SCK, TFT_RST);
// ST7789_t3 * tft = &tft0.driver;

void init_spi()
{
    SPI.setMOSI(K_SPI0_MOSI);
    SPI.setMISO(K_SPI0_MISO);
    SPI.setSCK(K_SPI0_SCK);

    SPI1.setMOSI(K_SPI1_MOSI);
    SPI1.setMISO(K_SPI1_MISO);
    SPI1.setSCK(K_SPI1_SCK);

    SPI.usingInterrupt(digitalPinToInterrupt(RFM69_D0));
    SPI.usingInterrupt(digitalPinToInterrupt(RFM95_D0));
    SPI.usingInterrupt(digitalPinToInterrupt(NRF24_INTERRUPT));
    // SPI1.usingInterrupt(digitalPinToInterrupt(TS0_IRQ));

    SPI.begin();
    SPI1.begin();
}

IntervalTimer timer0;
IntervalTimer timer1;
IntervalTimer timer_isr_log;
void init_interrupts()
{
    timer0.begin(isr_timer_led, 010000);
    timer1.begin(isr_lvgl_tick, 1000);
    // Initialize Rest Button
    // attachInterrupt(digitalPinToInterrupt(TS0_IRQ), isr_xpt, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON_RESET), isr_button_reset, HIGH);
    NVIC_SET_PRIORITY(digitalPinToInterrupt(BUTTON_RESET), 0);

    // timer_isr_log.begin(isr_timer_log, 250000); // half second
}
void init_pins()
{
    pinMode(RFM69_CS, OUTPUT);
    pinMode(RFM69_D0, INPUT);
    pinMode(RFM95_NSS, OUTPUT);
    pinMode(NRF24_CE, OUTPUT);

    digitalWriteFast(RFM69_CS, HIGH);
    digitalWriteFast(RFM95_NSS, HIGH);
    digitalWriteFast(NRF24_CE, HIGH);

    pinMode(BUTTON_RESET, INPUT_PULLDOWN);
    pinMode(TS0_IRQ, INPUT);
}

extern lv_color_t buf1;
void init_peripherals()
{
    status_LED.setRGB(0, 255, 0);
    // Touchpad for touchscreen
    if (!xpt.begin(SPI1))
        Serial.println("Touch fail");
    else
        xpt.setRotation(3);

    // Display
    tft0.init(TFT0_WIDTH, TFT0_HEIGHT);
    tft0.invertDisplay(false);
    //tft0.setTextColor(ST77XX_WHITE);
    if (!lv_is_initialized()) Serial.println("LVGL Failed?");
    //tft0.fillScreen(ST77XX_BLACK);
    tft0.setRotation(1);
    //lv_init();
    // tft.setFrameBuffer( (uint16_t *) buf1);
    // tft.useFrameBuffer(true);

    // logger("TFT Initialized.");

    // Begin RF69
    /*
    int stat = rf69.begin(915);

    if (stat != RADIOLIB_ERR_NONE)
    {
        Serial.println("Rf69 init fail");
        logger("RF69 Init fail: " + String(stat));
    }

    rf69.setDio0Action(isr_rf69);
    //rf69.setRxBandwidth(250);
    rf69.startReceive();

    nnrf95.begin();1
    stat = nnrf95.setRecieveIRQ(isr_rf95, RFM95_NSS);
    logger(stat);

    stat = nrf24.begin();
    if (stat != RADIOLIB_ERR_NONE)
    {
        logger("NRF24 Fail" + String(stat));
    }
    nrf24.setIrqAction(isr_nrf24);
    nrf24.startReceive();
    */
    // Begin RFC522

    // Begin Teensy onboard ethernet
    //
    // Link state event listener, execute on yield()
    /*
    Ethernet.onLinkState([](bool state)
                         { logger("Link State: " + String((state) ? "ON" : "OFF")); });
    // Super elite-hacker MAC address
    uint8_t mac[] = {0xFE, 0xED, 0xDE, 0xAD, 0xBE, 0xEF};
    Ethernet.setHostname("talos");
    Ethernet.setMACAddress(mac);

    Ethernet.onAddressChanged(
        []()
        {
            uint8_t mac[6]{0};
            char message[100];
            const char *fmt = "IP: %s\n"
                              "Hostname: %s\n"
                              "Gateway: %s\n"
                              "DNS: %s\n"
                              "MAC: %s";
            Ethernet.macAddress(mac);

            sprintf(message, fmt,
                    IPv4ToString(Ethernet.localIP()).c_str(),
                    Ethernet.hostname().c_str(),
                    IPv4ToString(Ethernet.gatewayIP()).c_str(),
                    IPv4ToString(Ethernet.dnsServerIP()).c_str(),
                    MACFormat(mac).c_str());
            logger(message);
        });
    if (!Ethernet.begin()) //(!Ethernet.begin(IPAddress(192, 168, 1, 233), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 1)))
        logger("Unable to start ethernet!");

    File root;
    if (!SD.begin(BUILTIN_SDCARD))
    {
        logger("Failed to initialize onboard SD card.");
    }
    else
    {
        root = SD.open("/");
        if (!root)
            logger("Failed to open SD card root!");
    }
    File dir;
    String s;
    logger("Listing files on root of SD: ");
    while (dir = root.openNextFile())
    {
        if (!dir)
            break;
        s += String(dir.name()) + ", ";
    }
    if (s)
        logger(s);
*/
}

void init_lvgl()
{
    UI_Controller.init_logger_list(UI_Controller.dtc.at(0)->display);
}


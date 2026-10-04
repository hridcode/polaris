#include <Arduino.h>
#include <PicoDVI.h>
#include <RTClib.h>
#include <Wire.h>
#include <Fonts/FreeMono12pt7b.h>

static const struct dvi_serialiser_cfg dviConfig = {
    .pio = pio0,
    .sm_tmds = {0, 1, 2},
    .pins_tmds = {28, 30, 32},
    .pins_clk = 34,
    .invert_diffpairs = false
};

DVIGFX16 display(
    DVI_RES_400x240p60,
    dviConfig
);

RTC_DS3231 rtc;

void setup() {
    Serial.begin(115200);

    Wire.setSCL(13);
    Wire.setSDA(12);

    if (!rtc.begin()) {
        Serial.println("[SETUP] RTC not found.");
    }

    if (rtc.lostPower()) {
        Serial.println("[SETUP] RTC lost power, setting time.");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    Serial.println('Hello world!');
}

void loop() {
    DateTime now = rtc.now();

    // Draw time

    display.setFont(&FreeMono12pt7b);
    display.setTextColor(0xFFFF);
    display.setCursor(5, 5);

    display.print(now.day(), DEC);
    display.print('/');
    display.print(now.month(), DEC);
    display.print('/');
    display.print(now.year(), DEC);
    display.print(' ');

    display.print(now.hour(), DEC);
    display.print(':');
    display.print(now.minute(), DEC);
    display.print(':');
    display.print(now.second(), DEC);
    display.print(':');
}
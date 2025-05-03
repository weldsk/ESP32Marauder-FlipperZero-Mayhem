#include "led.h"

#ifndef BOARD_BW16
#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif

#ifdef BOARD_ESP32_C6
Adafruit_NeoPixel rgbLed(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
#elif defined(BOARD_ESP32_S3)
#ifndef RGB_BUILTIN
Adafruit_NeoPixel rgbLed(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
#endif
#endif

namespace FlipperHTTP
{

void LED::blink(int timeout)
{
#ifdef BOARD_WIFI_DEV
    // turn off RED and BLUE
    digitalWrite(6, LED_OFF); // RED
    digitalWrite(4, LED_OFF); // BLUE

    // turn on/off GREEN
    digitalWrite(5, LED_ON); // GREEN
    delay(timeout);
    digitalWrite(5, LED_OFF); // GREEN
    delay(timeout);
#elif defined(BOARD_ESP32_C6)
    // turn on GREEN
    rgbLed.setPixelColor(0, rgbLed.Color(COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b));
    rgbLed.show();
    delay(timeout);
    // turn off GREEN
    rgbLed.setPixelColor(0, rgbLed.Color(COLOR_OFF.r, COLOR_OFF.g, COLOR_OFF.b));
    rgbLed.show();
    delay(timeout);
#elif defined(BOARD_ESP32_CAM)
    // turn on GREEN
    digitalWrite(4, LED_ON); // GREEN
    delay(timeout);
    // turn off GREEN
    digitalWrite(4, LED_OFF); // GREEN
    delay(timeout);
#elif defined(BOARD_ESP32_S3)
#ifdef RGB_BUILTIN
    neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); // Green
    delay(timeout);
    neopixelWrite(RGB_BUILTIN, 0, 0, 0); // Off / black
    delay(timeout);
#endif
#elif defined(BOARD_ESP32_WROOM)
    // turn on GREEN
    digitalWrite(2, LED_ON); // GREEN
    delay(timeout);
    // turn off GREEN
    digitalWrite(2, LED_OFF); // GREEN
    delay(timeout);
#elif defined(BOARD_ESP32_WROVER)
    // turn off RED and BLUE
    digitalWrite(6, LED_OFF); // RED
    digitalWrite(4, LED_OFF); // BLUE

    // turn on/off GREEN
    digitalWrite(5, LED_ON); // GREEN
    delay(timeout);
    digitalWrite(5, LED_OFF); // GREEN
    delay(timeout);
#elif defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    // turn on GREEN
    digitalWrite(LED_BUILTIN, LED_ON);
    delay(timeout);
    // turn off GREEN
    digitalWrite(LED_BUILTIN, LED_OFF);
    delay(timeout);
#elif defined(BOARD_ESP32_C3)
    // turn on GREEN
    digitalWrite(8, LED_ON); // GREEN
    delay(timeout);
    // turn off GREEN
    digitalWrite(8, LED_OFF); // GREEN
    delay(timeout);
#elif defined(BOARD_BW16)
    // turn on GREEN
    digitalWrite(LED_B, LED_ON);
    delay(timeout);
    // turn off GREEN
    digitalWrite(LED_B, LED_OFF);
    delay(timeout);
#endif
}

void LED::start()
{
#ifdef BOARD_WIFI_DEV
    pinMode(4, OUTPUT); // Set Blue Pin mode as output
    pinMode(5, OUTPUT); // Set Green Pin mode as output
    pinMode(6, OUTPUT); // Set Red Pin mode as output

    digitalWrite(4, LED_OFF); // BLUE
    digitalWrite(6, LED_OFF); // RED
#elif defined(BOARD_ESP32_C6)
    rgbLed.begin();
    rgbLed.show();
#elif defined(BOARD_ESP32_CAM)
    pinMode(4, OUTPUT); // Set Green Pin mode as output
#elif defined(BOARD_ESP32_S3)
#ifdef RGB_BUILTIN
    // No need to initialize the RGB LED
#else
    rgbLed.begin();
    rgbLed.show();
#endif
#elif defined(BOARD_ESP32_WROOM)
    pinMode(2, OUTPUT); // Set Green Pin mode as output
#elif defined(BOARD_ESP32_WROVER)
    pinMode(4, OUTPUT); // Set Blue Pin mode as output
    pinMode(5, OUTPUT); // Set Green Pin mode as output
    pinMode(6, OUTPUT); // Set Red Pin mode as output

    digitalWrite(4, LED_OFF); // BLUE
    digitalWrite(6, LED_OFF); // RED
    digitalWrite(5, LED_OFF); // GREEN
#elif defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    pinMode(LED_BUILTIN, OUTPUT); // Set Green Pin mode as output
#elif defined(BOARD_ESP32_C3)
    pinMode(8, OUTPUT); // Set Green Pin mode as output
#elif defined(BOARD_BW16)
    pinMode(LED_B, OUTPUT); // it says blue, but shows up as green
#endif
    this->blink();
    this->blink();
    this->blink();
}

void LED::on()
{
#ifdef BOARD_WIFI_DEV
    digitalWrite(4, LED_OFF); // BLUE
    digitalWrite(6, LED_OFF); // RED
    digitalWrite(5, LED_ON);  // GREEN
#elif defined(BOARD_ESP32_C6)
    rgbLed.setPixelColor(0, rgbLed.Color(COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b));
    rgbLed.show();
#elif defined(BOARD_ESP32_CAM)
    digitalWrite(4, LED_ON); // GREEN
#elif defined(BOARD_ESP32_S3)
#ifdef RGB_BUILTIN
    neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); // Green
#else
    rgbLed.setPixelColor(0, rgbLed.Color(COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b));
    rgbLed.show();
#endif
#elif defined(BOARD_ESP32_WROOM)
    digitalWrite(2, LED_ON); // GREEN
#elif defined(BOARD_ESP32_WROVER)
    digitalWrite(4, LED_OFF); // BLUE
    digitalWrite(6, LED_OFF); // RED
    digitalWrite(5, LED_ON);  // GREEN
#elif defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    digitalWrite(LED_BUILTIN, LED_ON); // GREEN
#elif defined(BOARD_ESP32_C3)
    digitalWrite(8, LED_ON); // GREEN
#elif defined(BOARD_BW16)
    digitalWrite(LED_B, LED_ON); // GREEN
#endif
}

void LED::off()
{
#ifdef BOARD_WIFI_DEV
    digitalWrite(4, LED_OFF); // BLUE
    digitalWrite(5, LED_OFF); // GREEN
    digitalWrite(6, LED_OFF); // RED
#elif defined(BOARD_ESP32_C6)
    rgbLed.setPixelColor(0, rgbLed.Color(COLOR_OFF.r, COLOR_OFF.g, COLOR_OFF.b));
    rgbLed.show();
#elif defined(BOARD_ESP32_CAM)
    digitalWrite(4, LED_OFF); // GREEN
#elif defined(BOARD_ESP32_S3)
#ifdef RGB_BUILTIN
    neopixelWrite(RGB_BUILTIN, 0, 0, 0); // Off / black
#else
    rgbLed.setPixelColor(0, rgbLed.Color(COLOR_OFF.r, COLOR_OFF.g, COLOR_OFF.b));
    rgbLed.show();
#endif
#elif defined(BOARD_ESP32_WROOM)
    digitalWrite(2, LED_OFF); // GREEN
#elif defined(BOARD_ESP32_WROVER)
    digitalWrite(4, LED_OFF); // BLUE
    digitalWrite(5, LED_OFF); // GREEN
    digitalWrite(6, LED_OFF); // RED
#elif defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    digitalWrite(LED_BUILTIN, LED_OFF); // GREEN
#elif defined(BOARD_ESP32_C3)
    digitalWrite(8, LED_OFF); // GREEN
#elif defined(BOARD_BW16)
    digitalWrite(LED_B, LED_OFF); // GREEN
#endif
}

} // namespace FlipperHTTP

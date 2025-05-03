#pragma once
#include <Arduino.h>
#include "boards.h"

namespace FlipperHTTP
{

class LED
{
public:
    void blink(int timeout = 250); // Turn on and off the LED
    void start();                  // Display LED sequence
    void on();                     // Turn on LED (Green only)
    void off();                    // Turn off all LEDs
};

#ifdef BOARD_ESP32_C6
#include <Adafruit_NeoPixel.h>

constexpr uint8_t LED_PIN = 10;
constexpr uint8_t NUM_LEDS = 1;

// Use extern declaration instead of definition:
extern Adafruit_NeoPixel rgbLed;

struct RGB
{
    uint8_t r, g, b;
};

constexpr RGB COLOR_OFF = {0, 0, 0};
constexpr RGB COLOR_GREEN = {0, 255, 0};

#elif defined(BOARD_ESP32_S3)
#ifndef RGB_BUILTIN
#include <Adafruit_NeoPixel.h>

constexpr uint8_t LED_PIN = 48;
constexpr uint8_t NUM_LEDS = 1;

// Use extern declaration:
extern Adafruit_NeoPixel rgbLed;

struct RGB
{
    uint8_t r, g, b;
};

constexpr RGB COLOR_OFF = {0, 0, 0};
constexpr RGB COLOR_GREEN = {0, 255, 0};
#endif
#elif defined(BOARD_ESP32_C3)
#include <Adafruit_NeoPixel.h>

// The LED pin may differ for whatever board you are using
constexpr uint8_t LED_PIN = 8;
constexpr uint8_t NUM_LEDS = 1;

// Use extern declaration:
extern Adafruit_NeoPixel rgbLed;

struct RGB
{
    uint8_t r, g, b;
};

constexpr RGB COLOR_OFF = {0, 0, 0};
constexpr RGB COLOR_GREEN = {0, 255, 0};
#endif

} // namespace FlipperHTTP

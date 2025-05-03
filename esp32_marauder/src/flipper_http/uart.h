#pragma once
#include <Arduino.h>
#include "boards.h"

namespace FlipperHTTP
{

class UART
{
public:
    size_t available();
    void begin(uint32_t baudrate);
    void flush();
    void clear_buffer();
    void print(String str);
    void printf(const char *format, ...);
    void println(String str = "");
    uint8_t read();
    uint8_t readBytes(uint8_t *buffer, size_t size);
    String read_serial_line();
    void set_timeout(uint32_t timeout);
    void write(const uint8_t *buffer, size_t size);
#ifdef BOARD_VGM
    void set_pins(uint8_t tx_pin, uint8_t rx_pin);
#endif
private:
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W)
    SerialPIO *serial;
#elif defined(BOARD_VGM)
    SerialPIO *serial;
    uint8_t rx_pin;
    uint8_t tx_pin;
#endif
};

} // namespace FlipperHTTP

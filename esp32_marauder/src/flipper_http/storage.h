#pragma once
#include "boards.h"
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
#include <LittleFS.h>
#elif defined(BOARD_BW16)
#include <FlashStorage_RTL8720.h> // https://github.com/khoih-prog/FlashStorage_RTL8720
#elif defined(BOARD_MAYHEM)
#include <SD_MMC.h>
#else
#include <SPIFFS.h>
#endif
#include <ArduinoJson.h>

namespace FlipperHTTP
{

bool file_begin();
void file_deserialize(JsonDocument &doc, const char *filename);
String file_read(const char *filename);
void file_serialize(JsonDocument &doc, const char *filename);
bool file_write(const char *filename, const char *data);
size_t free_heap();

} // namespace FlipperHTTP

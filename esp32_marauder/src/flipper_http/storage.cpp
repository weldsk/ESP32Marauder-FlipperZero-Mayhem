#include "storage.h"

namespace FlipperHTTP
{

bool file_begin()
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    if (!LittleFS.begin())
    {
        if (LittleFS.format())
        {
            if (!LittleFS.begin())
            {
                return false;
            }
        }
        return false;
    }
    return true;
#elif defined(BOARD_BW16)
    // no begin needed
    return true;
#elif defined(BOARD_MAYHEM)
    return SD_MMC.begin("/sdcard", true, false, SDMMC_FREQ_DEFAULT);
#else
    if (!SPIFFS.begin(true))
    {
        return false;
    }
    return true;
#endif
}

void file_deserialize(JsonDocument &doc, const char *filename)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "r");
#elif defined(BOARD_MAYHEM)
    File file = SD_MMC.open(filename, FILE_READ);
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_READ);
#endif
#ifndef BOARD_BW16
    deserializeJson(doc, file);
    file.close();
#else
    /*We will keep all data at the same address and overwrite for now*/
    int bw16_flash_address = sizeof(filename); // Location we want the data to be put.
    char buffer[512];
    FlashStorage.get(bw16_flash_address, buffer);
    buffer[sizeof(buffer) - 1] = '\0'; // Null-terminate the string
    deserializeJson(doc, buffer);
#endif
}

String file_read(const char *filename)
{
    String fileContent = "";
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "r");
#elif defined(BOARD_MAYHEM)
    File file = SD_MMC.open(filename, FILE_READ);
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_READ);
#endif
#ifndef BOARD_BW16
    if (file)
    {
        // Read the entire file content
        fileContent = file.readString();
        file.close();
    }
#else
    /*We will keep all data at the same address and overwrite for now*/
    int bw16_flash_address = sizeof(filename); // Location we want the data to be put.
    FlashStorage.get(bw16_flash_address, fileContent);
#endif
    return fileContent;
}

void file_serialize(JsonDocument &doc, const char *filename)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "w");
#elif defined(BOARD_MAYHEM)
    File file = SD_MMC.open(filename, FILE_WRITE);
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_WRITE);
#endif
#ifndef BOARD_BW16
    if (file)
    {
        serializeJson(doc, file);
        file.close();
    }
#else
    /*We will keep all data at the same address and overwrite for now*/
    int bw16_flash_address = sizeof(filename); // Location we want the data to be put.
    char buffer[512];
    size_t len = serializeJson(doc, buffer, sizeof(buffer));
    buffer[len] = '\0'; // Null-terminate the string
    FlashStorage.put(bw16_flash_address, buffer);
#endif
}

bool file_write(const char *filename, const char *data)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "w");
#elif defined(BOARD_MAYHEM)
    File file = SD_MMC.open(filename, FILE_WRITE);
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_WRITE);
#endif
#ifndef BOARD_BW16
    if (file)
    {
        file.print(data);
        file.close();
        return true;
    }
#else
    /*We will keep all data at the same address and overwrite for now*/
    int bw16_flash_address = sizeof(filename); // Location we want the data to be put.
    FlashStorage.put(bw16_flash_address, data);
#endif
    return false;
}

size_t free_heap()
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    return rp2040.getFreeHeap();
#elif defined(BOARD_BW16)
    return os_get_free_heap_size_arduino();
#else
    return ESP.getFreeHeap();
#endif
}

} // namespace FlipperHTTP

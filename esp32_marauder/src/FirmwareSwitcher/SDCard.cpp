#include "SDCard.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32

FirmwareSwitcher::SDCard::SDCard()
    :is_valid(false)
{
    if (!SD_MMC.begin("/sdcard", true, false, SDMMC_FREQ_DEFAULT))
    {
        return;
    }
    auto cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE)
    {
        return;
    }
    is_valid = true;
}

FirmwareSwitcher::SDCard::~SDCard()
{
    if (!is_valid)
    {
        return;
    }
    is_valid = false;
}

String FirmwareSwitcher::SDCard::readFile(const String &filepath)
{
    if (!is_valid)
    {
        return String();
    }
    File file = SD_MMC.open(filepath, FILE_READ);
    if (file)
    {
        String content = file.readString();
        file.close();
        return content;
    }
    return String();
}

bool FirmwareSwitcher::SDCard::writeFile(const String &filepath, const String &str)
{
    if (!is_valid)
    {
        return false;
    }
    File file = SD_MMC.open(filepath, FILE_WRITE, true);
    if (file)
    {
        size_t written_size = file.write(
            reinterpret_cast<const uint8_t*>(str.c_str()), str.length());
        file.close();
        return written_size >= str.length();
    }
    return String();
}

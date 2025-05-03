#include "FirmwareSwitcher.h"
#include "FirmwareSwitcher/SDCard.h"

namespace FirmwareSwitcher
{
    static SDCard* sd_card = nullptr;
    String readFirmwareName()
    {
        if (!sd_card) {
            sd_card = new SDCard();
        }
        return sd_card->readFile(FILE_NAME);
    }
    bool writeFirmwareName(String& name)
    {
        if (!sd_card) {
            sd_card = new SDCard();
        }
        return sd_card->writeFile(FILE_NAME, name);
    }
}

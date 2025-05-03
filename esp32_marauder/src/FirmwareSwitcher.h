#pragma once
#include <ArduinoJson.h>

namespace FirmwareSwitcher
{
    inline static const String FILE_NAME = "/firmware_switcher.txt";
    String readFirmwareName();
    bool writeFirmwareName(String& name);
}

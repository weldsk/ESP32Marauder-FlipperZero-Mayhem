#pragma once
#include <ArduinoJson.h>

namespace FirmwareSwitcher
{
    class SDCard
    {
        public:
            SDCard();
            ~SDCard();
            String readFile(const String &filepath);
            bool writeFile(const String &filename, const String &str);
        private:
            bool is_valid;
    };
}

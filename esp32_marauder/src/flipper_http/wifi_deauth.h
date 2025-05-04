#pragma once
#include "boards.h"

namespace FlipperHttp
{
class WiFiDeauth
{
public:
    bool start(const char *ssid);
    void stop();
    void update();
};

}

#pragma once
#include <Arduino.h>
#include "boards.h"
#ifndef BOARD_BW16
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#else
#include "WiFiClient.h"
#include "WiFiServer.h"
#endif
#include "WiFi.h"

namespace FlipperHTTP
{

class WiFiUtils
{
public:
    WiFiUtils()
    {
    }

    bool connect(const char *ssid, const char *password); // Connect to WiFi using the provided SSID and password
    String device_ip();                                   // Get IP address of the device
    void disconnect();                                    // Disconnect from WiFi
    bool is_connected();                                  // Check if connected to WiFi
    String scan();                                        // Scan for available WiFi networks
};

} // namespace FlipperHTTP

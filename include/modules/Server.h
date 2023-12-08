
#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

class CarServer
{
private:
    static const char *ssid;
    static const char *password;
    static char *stats;
    static int statLength;

    static AsyncWebServer server;

public:
    static char getStat(int index);
    static void setStat(int index, char value);
    static int getStatLength();
    static void begin(const char *ssid, const char *password, int statLength);
};

#endif

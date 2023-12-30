
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Credentials.h"

boolean connected = false;
void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!\n");
        return;
    }

    connected = WiFi.waitForConnectResult() != WL_CONNECTED;
}

void loop()
{
    if (connected)
    {
        Serial.println("test vscode for esp32 connected to wifi");
    }
    else
    {
        Serial.println("test vscode for esp32 not connected to wifi");
    }
    delay(1000);
}
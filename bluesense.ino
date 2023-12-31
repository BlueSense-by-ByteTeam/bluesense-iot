#include <PubSubClient.h>

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "Credentials.h"
#include "Certificate.h"
#include "./src/services/sensors/Ph.h"
#include "./src/services/sensors/Tds.h"

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);
const char *topic = "esp32/dev";

boolean connected = false;
// median filtering algorithm

void setup()
{
    Serial.begin(115200);

    // setupWifi();

    // client.setServer(mqtt_server, mqtt_port);
    // client.setCallback(callback);
    // client.subscribe(topic);
    setupTds();
}

void setupWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!\n");
        return;
    }

    connected = WiFi.waitForConnectResult() != WL_CONNECTED;

    Serial.println(WiFi.localIP());
    wifiClient.setInsecure();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void reconnect()
{
    while (!client.connected())
    {
        String client_id = "esp32-bluesense-";
        client_id += String(WiFi.macAddress());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
        {
            Serial.println("Public emqx mqtt broker connected");
        }
        else
        {
            Serial.println("failed with state ");
            Serial.println(client.state());
        }
    }
}

void loop()
{
    // printSensorValue();
    tdsLoop();
    // if (connected)
    // {
    //     Serial.println("test vscode for esp32 connected to wifi");
    // }
    // else
    // {
    //     Serial.println("test vscode for esp32 not connected to wifi");
    // }

    // if (!client.connected())
    // {
    //     reconnect();
    // }
    // else
    // {
    //     client.publish(topic, "datetime");
    // }
    // client.loop();
    // delay(500);
}
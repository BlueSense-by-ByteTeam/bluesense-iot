
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Credentials.h"

WiFiClient espClient;
PubSubClient client(espClient);
const char *topic = "esp32/dev"; // define topic

boolean connected = false;
void setup()
{
    Serial.begin(115200);
    setupWifi();

    client.setServer(mqtt_server, 8883);
    client.setCallback(callback);
    client.subscribe(topic);
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

    while (!client.connected())
    {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
        {
            Serial.println("Public emqx mqtt broker connected");
        }
        else
        {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

    // char const *datetime = reinterpret_cast<char const *>(millis());
    client.publish(topic, "datetime");
    delay(500);
}
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Arduino.h>

void setupPostLogToServer(){
  Serial.begin(115200);
}

void postLogToServer(WiFiClientSecure wifiClient, String formattedMacAddress, float tds, float ph)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        if (wifiClient)
        {
            // create an HTTPClient instance
            HTTPClient https;
            // Initializing an HTTPS communication using the secure client
            Serial.print("[HTTPS] begin...\n");
            if (https.begin(wifiClient, "https://bluesenseapi-1-l2019661.deta.app/api/devices/logs"))
            { // HTTPS
                Serial.print("[HTTPS] POST LOG...\n");
                // start connection and send HTTP header
                https.addHeader("Content-Type", "application/json");
                StaticJsonDocument<200> jsonDoc;
                jsonDoc["device_id"] = formattedMacAddress;
                jsonDoc["ph"] = ph;
                jsonDoc["tds"] = tds;

                String jsonString;
                serializeJson(jsonDoc, jsonString);
                int httpResponseCode = https.POST(jsonString);
                // // httpCode will be negative on error
                if (httpResponseCode > 0)
                {
                    Serial.printf("[HTTPS] POST... code: %d\n", httpResponseCode);
                    if (httpResponseCode == HTTP_CODE_OK || httpResponseCode == HTTP_CODE_MOVED_PERMANENTLY)
                    {
                        // print server response payload
                        String payload = https.getString();
                        Serial.println(payload);
                    }
                }
                else
                {
                    // Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
                    Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpResponseCode).c_str());
                }
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);

                https.end();
            }
        }
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Arduino.h>

#include <PubSubClient.h>
#include <Arduino.h>

#include <WiFiClientSecure.h>
#include "Credentials.h"
// #include "Certificate.h"
#include "./src/services/sensors/Tds.h"
#include "./src/services/sensors/Ph.h"
#include "./src/services/logs/PostLog.h"

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

float tdsVal = 0;
float phVal = 0;
float voltage = 0;

String macAddress;

const unsigned long interval = 60000 * 10;      // Set the interval in milliseconds
const unsigned long intervalMqttPost = 1000;  // Set the interval in milliseconds
unsigned long previousMillis = 0;
unsigned long previousMillisMqttPost = 0;

void setup() {
  Serial.begin(115200);
  
  setupTds();
  setupPh();
  setupPostLogToServer();
  setupWifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.subscribe("esp32/dev");
}
void setupWifi() {
  const char *ssid = "awikwok";
  const char *password = "888#0N0d";
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!\n");
    // return;
  }

  macAddress = WiFi.macAddress();
  macAddress.replace(":", "");
  Serial.println(macAddress);

  // connected = WiFi.waitForConnectResult() != WL_CONNECTED;

  Serial.println(WiFi.localIP());
  wifiClient.setInsecure();
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void reconnect() {
  while (!client.connected()) {

    if (client.connect(macAddress.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.println("failed with state ");
      Serial.println(client.state());
    }
  }
}

void loop() {
  // printSensorValue();
  tdsLoop(&tdsVal);
  loopPh(&phVal);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // postLogToServer(wifiClient, macAddress, tdsVal, phVal);
    if (WiFi.status() == WL_CONNECTED) {
      if (wifiClient) {
        // create an HTTPClient instance
        HTTPClient https;
        // Initializing an HTTPS communication using the secure client
        Serial.print("[HTTPS] begin...\n");
        if (https.begin(wifiClient, serverName)) {  // HTTPS
          Serial.print("[HTTPS] POST LOG...\n");
          // start connection and send HTTP header
          https.addHeader("Content-Type", "application/json");
          StaticJsonDocument<200> jsonDoc;
          jsonDoc["device_id"] = macAddress;
          jsonDoc["ph"] = phVal;
          jsonDoc["tds"] = tdsVal;

          String jsonString;
          serializeJson(jsonDoc, jsonString);
          int httpResponseCode = https.POST(jsonString);
          // // httpCode will be negative on error
          if (httpResponseCode > 0) {
            Serial.printf("[HTTPS] POST... code: %d\n", httpResponseCode);
            if (httpResponseCode == HTTP_CODE_OK || httpResponseCode == HTTP_CODE_MOVED_PERMANENTLY) {
              // print server response payload
              String payload = https.getString();
              Serial.println(payload);
            }
          } else {
            // Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpResponseCode).c_str());
          }
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);

          https.end();
        }
      }
    } else {
      Serial.println("WiFi Disconnected");
    }
    previousMillis = currentMillis;
  }


  if (!client.connected()) {
    reconnect();
  } else {

    if (currentMillis - previousMillisMqttPost >= intervalMqttPost) {
      StaticJsonDocument<200> jsonDoc;
      // JsonObject phObj = jsonDoc.createNestedObject("ph");
      jsonDoc["ph"] = phVal;
      jsonDoc["tds"] = tdsVal;

      String jsonString;
      serializeJson(jsonDoc, jsonString);
      client.publish("esp32/dev", jsonString.c_str());

      Serial.println(jsonString);

      previousMillisMqttPost = currentMillis;
    }
  }
  client.loop();
}

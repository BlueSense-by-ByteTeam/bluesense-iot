# 1 "D:\\codings\\arduino\\bluesense\\bluesense.ino"

# 3 "D:\\codings\\arduino\\bluesense\\bluesense.ino" 2
# 4 "D:\\codings\\arduino\\bluesense\\bluesense.ino" 2
# 5 "D:\\codings\\arduino\\bluesense\\bluesense.ino" 2
# 6 "D:\\codings\\arduino\\bluesense\\bluesense.ino" 2

boolean connected = false;
void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
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

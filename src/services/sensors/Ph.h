
// #include "DFRobot_ESP_PH.h"
// #include <EEPROM.h>

// DFRobot_ESP_PH ph;
// #define ESPADC 4096.0   // the esp Analog Digital Convertion value
// #define ESPVOLTAGE 3300 // the esp voltage supply value
// #define PH_PIN 35       // the esp gpio data pin number
// float voltage, phValue, temperature = 25;

// void setup()
// {
//     Serial.begin(115200);
//     EEPROM.begin(32); // needed to permit storage of calibration value in eeprom
//     ph.begin();
// }

// void loop()
// {
//     static unsigned long timepoint = millis();
//     if (millis() - timepoint > 1000U) // time interval: 1s
//     {
//         timepoint = millis();
//         // voltage = rawPinValue / esp32ADC * esp32Vin
//         voltage = analogRead(PH_PIN) / ESPADC * ESPVOLTAGE; // read the voltage
//         Serial.print("voltage:");
//         Serial.println(voltage, 4);

//         // temperature = readTemperature();  // read your temperature sensor to execute temperature compensation
//         Serial.print("temperature:");
//         Serial.print(temperature, 1);
//         Serial.println("^C");

//         phValue = ph.readPH(voltage, temperature); // convert voltage to pH with temperature compensation
//         Serial.print("pH:");
//         Serial.println(phValue, 4);
//     }
//     ph.calibration(voltage, temperature); // calibration process by Serail CMD
// }

// float readTemperature()
// {
//     // add your code here to get the temperature from your temperature sensor
// }
const int potPin = A0;
float ph;
float Value = 0;

void phSetup()
{
    pinMode(potPin, INPUT);
    delay(1000);
}
void phLoop()
{

    Value = analogRead(potPin);
    Serial.print(Value);
    Serial.print(" | ");
    float voltage = Value * (3.3 / 4095.0);
    ph = (3.3 * voltage);
    Serial.println(ph);
    delay(500);
}
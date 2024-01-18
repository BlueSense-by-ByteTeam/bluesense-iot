const int potPin = A0;
float ph;
float Value = 0;
int buf[10];

float phFormula(float voltage)
{
    return 7 + ((2.5 - voltage) / 0.18);
}

void setupPh()
{
    pinMode(potPin, INPUT);
    delay(1000);
}

void printPhValue()
{
    Serial.print(Value);
    Serial.print(" | ");
    Serial.println(ph);
}

void loopPh(float *value)
{
    for (int i = 0; i < 10; i++)
    {
        buf[i] = analogRead(potPin);
        delay(10);
    }
    // Serial.println("buffer");
    // Serial.println(analogRead(potPin));

    float avgValue = 0;
    for (int i = 0; i < 10; i++)
        avgValue += buf[i];

    float phVol = (float)avgValue * 5.0 / 1024 / 10;
    float phValue = -5.70 * phVol + 21.34;

    // Serial.print("ph formula");
    // Serial.println(phFormula(phVol));

    // Serial.print("ph value: ");
    // Serial.println(phValue);
    *value = phValue;
}

void phLoop(float *value)
{
    Value = analogRead(potPin);
    float voltage = Value * (3.3 / 4095.0);
    ph = (3.3 * voltage);
    *value = ph;

    printPhValue();
}


#include "./../../helper/Char.h"
#include <string.h>

void printSensorValue()
{
    long currentDate = millis();
    char *dateChar;

    longToCharArray(currentDate, &dateChar);

    // char message[] = "sensor dummy value x get by: ";
    // strcat(message, dateChar);

    Serial.println(dateChar);
    free(dateChar);
}
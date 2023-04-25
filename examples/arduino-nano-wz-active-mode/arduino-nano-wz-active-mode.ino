#include "WZ.h"
#include <SoftwareSerial.h>

/////////////////////////// Arduino Nano Board
/*
 * There is only one serial port on the Arduino Nano, so software serial is needed to connect to the sensor. 
 */
const byte PIN_RX = 8; // define software serial RX pin
const byte PIN_TX = 9; // define software serial TX pin
SoftwareSerial WzSoftSerial(PIN_RX, PIN_TX);
WZ wz(WzSoftSerial);
WZ::DATA hcho_data;

void setup()
{
    Serial.begin(9600);
    WzSoftSerial.begin(9600);
    //wz.activeMode();
}

void loop()
{
    if (wz.read(hcho_data))
    {
        Serial.print("HCHO (ppd): ");
        Serial.println(hcho_data.HCHO_PPB);
        Serial.print("HCHO (ug/m3): ");
        Serial.println(hcho_data.HCHO_UGM3); // no data here, 0 returned
        Serial.println();
    }
    // Do other stuff...
}

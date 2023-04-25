#include "WZ.h"

/////////////////////////// ESP32-S NodeMCU Board
/*
 * There are three serial ports on the ESP32 known as UART0, UART1 and UART2.
 *
 * UART0 (GPIO1 - TX0, GPIO3 - RX0) is used to communicate with the ESP32 for programming and during reset/boot.
 * UART1 (GPIO10 - TX1, GPIO9 - RX1) is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * UART2 (GPIO17 - TX2, GPIO16 - RX2) is unused and can be used for your projects.
 *
 */

WZ wz(Serial2); // UART2
WZ::DATA hcho_data;

void setup()
{
    Serial.begin(115200);
    Serial2.begin(9600);
    wz.passiveMode();
}

void loop()
{
    wz.requestRead();
    if (wz.readUntil(hcho_data))
    {
        Serial.print("HCHO (ppd): ");
        Serial.println(hcho_data.HCHO_PPB);
        Serial.print("HCHO (ug/m3): ");
        Serial.println(hcho_data.HCHO_UGM3);
        Serial.println();
    }
    delay(1000);
    // Do other stuff...
}
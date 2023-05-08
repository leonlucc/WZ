# WZ Library
Arduino library for `Dart WZ-S`, `Prosense WZ-H3` and `Winsen ZE08-CH2O` formaldehyde (HCHO) sensors, using methods same with the [PMS](https://github.com/fu-hsi/PMS) Library. 

[中文介绍](https://github.com/leonlucc/WZ/blob/master/README-CN.md)

## Applicable Sensors
|brand|model|product documents|
|--|--|--|
|DART|WZ-S, WZ-S-K|[WZ-S module product detail](https://www.dart-sensors.com/product/wz-s-formaldehyde-module/) <br /> [WZ-S module manual](https://www.dart-sensors.com/wp-content/uploads/2017/07/formaldehyde_module_operation-manual.pdf)|
|Prosense|WS-H3, WS-H3-N|[WZ-H3 module product detail](https://www.szprosense.com/?list_28/41.html)<br /> [WZ-H3 module manual](https://www.szprosense.com/static/upload/file/20220208/1644312414263701.pdf)|
|Winsen|ZE08-CH2O, ZE08K-CH2O, ZE08B-CH2O|[ZE08-CH2O module product detail](https://www.winsensor.com/product/807.html)<br />[ZE08-CH2O module manual](https://cdn.myxypt.com/26ecc11e/22/06/bc6ccaec97adda754f03ed1c2f65899ceedcbdc9.pdf)|

## Installation
Just use Arduino Library Manager and search "WZ Library" in Sensors category.
## Basic Usage
### Read in active mode using ESP32-S board
```cpp
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
    // wz.activeMode();
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

```
### Read in passive mode using Arduino Nano board
```cpp
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
```

more examples [here](https://github.com/leonlucc/WZ/tree/main/examples)

## Acknowledgements
* this project is based on [PMZ](https://github.com/fu-hsi/PMS)
* this project is inspired by [WZ-S](https://github.com/Gillwindy/WZ-S) 

## License
* MIT
# WZ Library
面向达特WZ-S以及普晟WZ-H3系列传感器的Arduino开发库，支持WZ-S, WZ-S-K, WS-H3, WS-H3-N

## 安装
打开Arduino IDE -> 项目 -> 加载库 -> 管理库 -> 搜索  "WZ Library"

## 示例
### 主动模式读数，使用ESP32-S开发板
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
### 被动模式读数，使用Arduino Nano开发板
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

更多示例参考[这里](https://github.com/leonlucc/WZ/tree/main/examples)

## 手册 
* [WZ-S formaldehyde module product](https://www.dart-sensors.com/product/wz-s-formaldehyde-module/)
* [WZ-S formaldehyde module manual](https://www.dart-sensors.com/wp-content/uploads/2017/07/formaldehyde_module_operation-manual.pdf)
* [WZ-H3 module product](https://www.szprosense.com/?list_28/41.html)
* [WZ-H3 module manual](https://www.szprosense.com/static/upload/file/20220208/1644312414263701.pdf)

## 感谢
* 本项目基于[PMZ](https://github.com/fu-hsi/PMS)开发
* 本项目受[WZ-S](https://github.com/Gillwindy/WZ-S) 启发

## License
* MIT
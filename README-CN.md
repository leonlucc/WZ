# WZ Library
面向`达特WZ-S`、`普晟WZ-H3`、`炜盛ZE08-CH2O`系列甲醛传感器的Arduino开发库

## 适用的传感器
|品牌|型号|产品文档|
|--|--|--|
|达特|WZ-S, WZ-S-K|[WZ-S模组介绍](https://www.dart-sensors.com/product/wz-s-formaldehyde-module/) <br /> [WZ-S模组技术手册](https://www.dart-sensors.com/wp-content/uploads/2017/07/formaldehyde_module_operation-manual.pdf)|
|普晟|WS-H3, WS-H3-N|[WZ-H3模组介绍](https://www.szprosense.com/?list_28/41.html)<br /> [WZ-H3模组技术手册](https://www.szprosense.com/static/upload/file/20220208/1644312414263701.pdf)|
|炜盛|ZE08-CH2O, ZE08K-CH2O, ZE08B-CH2O|[ZE08-CH2O模组介绍](https://www.winsensor.com/product/807.html)<br />[ZE08-CH2O模组技术手册](https://cdn.myxypt.com/26ecc11e/22/06/bc6ccaec97adda754f03ed1c2f65899ceedcbdc9.pdf)|

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

## 感谢
* 本项目基于[PMZ](https://github.com/fu-hsi/PMS)开发
* 本项目受[WZ-S](https://github.com/Gillwindy/WZ-S) 启发

## License
* MIT
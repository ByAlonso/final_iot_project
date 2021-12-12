# 34365 IoT Prototyping Elderwell: Smart Platform For Elder Care
## Sensor device setup
In order to start using the sensor device, some things must be taken into account.
### Components
The following components are required to successfully get all device functionality:
- NodeMCU esp8266 wifi https://tienda.bricogeek.com/wifi/1033-nodemcu-v3-wifi-esp8266-ch340.html
- rn2483 LoRa Module https://www.tindie.com/products/drazzy/lorawan-rn2483rn2903-breakout-board-assembled/
- CO2 Sensor https://www.elextra.dk/p/GS/H16450?utm_source=GoogleAds&utm_medium=cpc&gclid=Cj0KCQiA2NaNBhDvARIsAEw55hiUin6cAYG8qKOm6sxs6GctD1uAz_RcJ_aWzyhUJ_8NLO1qmrbmBW4aAtAmEALw_wcB
- DHT11 Sensor https://minielektro.dk/dht11-modul-temperatur-og-fugtsensor.html?gclid=Cj0KCQiA2NaNBhDvARIsAEw55hiwo1KE4StQiR5vmblP7z-02RBTBftVgQOPUv-kv3Z2cRrDgx0ZDTwaAtfcEALw_wcB

### Libraries

This libraries should be installed in order to run the code successfully:
- <rn2xx3.h> https://github.com/jpmeijers/RN2483-Arduino-Library/blob/master/src/rn2xx3.h
- <SoftwareSerial.h> https://www.arduino.cc/en/Reference/SoftwareSerial
- <MG811.h> https://github.com/smart-tech-benin/MG811
- <DHT.h> https://www.arduino.cc/reference/en/libraries/dht-sensor-library/



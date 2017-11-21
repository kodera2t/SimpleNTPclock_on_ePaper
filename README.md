### SimpleNTPclock_on_ePaper

The ready-made board is avaiable at

https://www.tindie.com/products/microwavemont/epaper-plus-esp32-adb/

Simple Clock sample displaying current time on ePaper display. Before uploading binary to ePaper plus ESP32-ADB, backup your original 
```
pins_arduino.h
```
inside 
``
Arduino/hardware/espressif/esp32/variant/esp32
``
and replace with the file in this repository because SPI usage of ePaper plus ESP32-ADB is not same as original Arduino environment.
After replacing the file, just edit SSID/Password in line 18, 19 in ePaper_NTP_CLOCK.ino and ntp server in line 44 with your nearby ntp server.

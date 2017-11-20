//////////////////sample program ntp clock on ePaper
#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.cpp>
#include <WiFi.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>
#include <Fonts/FreeMonoBold18pt7b.h>//Fonts in Adafruit GFX library

GxIO_Class io(SPI, 4, 17, 16);
GxEPD_Class display(io, 16, 5);
const uint32_t partial_update_period_s = 1;
const uint32_t full_update_period_s = 6 * 60 * 60;

uint32_t start_time;
uint32_t next_time;
uint32_t next_full_update;

const char *ssid = "ssid";//fit to your ssid and password
const char *password = "password";

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  display.init();
  display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setRotation(0);
  display.update();
  display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
  display.setRotation(1);
  start_time = next_time = millis();
  next_full_update = start_time + full_update_period_s * 1000;
  if (WiFi.begin(ssid, password) != WL_DISCONNECTED) {
    ESP.restart();
  }
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("?");
  }
    Serial.printf("Connected, IP address: ");
    Serial.println(WiFi.localIP());
  configTime( -3600*9, 0, "ntp.jst.mfeed.ad.jp");///change to your nearby ntp server
  ///and also please adjust first argument of configTime( xxx,) to fit your local time.
}

void loop()
{
  time_t t;
  struct tm *tm;
  static const char *wd[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
  t = time(NULL);
  tm = localtime(&t);
  Serial.printf(" %2d/%02d/%02d(%s) %02d:%02d:%02d\n",
        tm->tm_year-100, tm->tm_mon+1, tm->tm_mday,
        wd[tm->tm_wday],
        tm->tm_hour, tm->tm_min, tm->tm_sec);
  showTime();
  delay(10000);
}

void showTime()
{
  uint16_t box_x = 0;
  uint16_t box_y = 0;
  uint16_t box_w = 195;
  uint16_t box_h = 195;
  uint16_t cursor_y = box_y + 16;
  struct tm timeInfo;
  char s[20];
  static const char *wd[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
 
  getLocalTime(&timeInfo);
  sprintf(s, "%2d/%02d/%02d\n(%s)\n%02d:%02d:%02d",
          timeInfo.tm_year-100, timeInfo.tm_mon + 1, timeInfo.tm_mday,wd[timeInfo.tm_wday],
          timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
  display.setCursor(box_x, 80);
  Serial.println(timeInfo.tm_min);
  display.printf(s);
  display.updateWindow(box_x, box_y, box_w, box_h, true);
}



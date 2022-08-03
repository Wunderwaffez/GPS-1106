#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <TinyGPS++.h>

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

TinyGPSPlus gps;
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n";

void setup() {
  oled.begin(i2c_Address, true);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.setCursor(0, 0);

  while (*gpsStream)
    if (gps.encode(*gpsStream++))
      displayInfo();

}

void loop() {


}

void displayInfo() {

  oled.setCursor(0, 27);
  oled.print("Enlem:");
  oled.setCursor(0, 35);
  oled.print("Boylam:");
  oled.setCursor(0, 43);
  oled.print("Yukseklik:");
  oled.setCursor(0, 51);
  oled.print("Uydu:");

  if (gps.time.isValid())
  {
    oled.setCursor(16, 0);
    oled.setTextSize(2);
    if (gps.time.hour() < 10) oled.print(F("0"));
    oled.print(gps.time.hour());
    oled.print(F(":"));
    if (gps.time.minute() < 10) oled.print(F("0"));
    oled.print(gps.time.minute());
    oled.print(F(":"));
    if (gps.time.second() < 10) oled.print(F("0"));
    oled.print(gps.time.second());
  }
  else
  {
    oled.setCursor(16, 0);
    oled.setTextSize(2);
    oled.print(F("ERR"));
  }

  if (gps.date.isValid())
  {
    oled.setCursor(40, 16);
    oled.setTextSize(1);
    oled.print(gps.date.month());
    oled.print(F("/"));
    oled.print(gps.date.day());
    oled.print(F("/"));
    oled.print(gps.date.year());
  }
  else
  {
    oled.setCursor(40, 16);
    oled.setTextSize(1);
    oled.print(F("error"));
  }

  oled.drawLine(0,25,127,25,SH110X_WHITE);

  if (gps.location.isValid())
  {
    oled.setCursor(36,27);
    oled.print(gps.location.lat(), 6);
    oled.setCursor(42,35);
    oled.print(gps.location.lng(), 6);
  }
  else
  {
    oled.setCursor(36,27);
    oled.print("veri yok");
    oled.setCursor(42,35);
    oled.print("veri yok");
  }

  if (gps.altitude.isValid())
  {
    oled.setCursor(61,43);
    oled.print(gps.altitude.meters(), 6);
  }
  else
  {
    oled.setCursor(61,43);
    oled.print("veri yok");
  }

  if (gps.satellites.isValid())
  {
    oled.setCursor(30,51);
    oled.print(gps.satellites.value(), 6);
  }
  else
  {
    oled.setCursor(30,51);
    oled.print("veri yok");
  }

  /*oled.setCursor(121,16);
  oled.print("1");
  oled.drawRoundRect(119,13,9,13,2,SH110X_WHITE);*/

  oled.setCursor(121,28);
  oled.print("1");
  oled.drawRoundRect(119,25,9,13,2,SH110X_WHITE);
  
  
  oled.display();
}

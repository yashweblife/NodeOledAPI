#include <Arduino.h>
#include <SSD1306Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

SSD1306Wire display(0x3c, SDA, SCL);

void setup() {
  display.init();
  display.clear();
  display.drawString(0, 0, "Hello World");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
}